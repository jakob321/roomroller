const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');

const port = 6969;
const server = http.createServer(express);
const wss = new WebSocket.Server({ server })

const app = express();

// websocket comunication
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(data) {
    wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(data.toString());
      }
    })
  })
})

server.listen(port, function() {
  console.log(`Server is listening on ${port}!`)
})

console.log('Server started at http://localhost:' + port);


// serves the website to the client
app.get('/', function(req, res) {
  res.sendFile(path.join(__dirname, '/index.html'));
});
app.listen(8000);
console.log('Server started at http://localhost:' + 8000);