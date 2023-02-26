// Imports
const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');
const shm = require('./shmnode/build/Debug/shmnode.node') // c++ addon

const app = express()
const server = http.createServer(express);
const wss = new WebSocket.Server({ server })

const port_message = 8001;
const port_web = 8000

/* -------------------------------------------
    Websocket comunication
--------------------------------------------*/

//listens for messages from the client
wss.on('connection', function connection(ws) {
    ws.on('message', function incoming(data) {
        data_str = data.toString();
        console.log("recieved: " + data_str);
        if(data_str == "ping"){
            send_message("ping-response");
        } else{
            send_queue.push(data_str);
        }  
    })
})

// send message to client
function send_message(message) {
    console.log("sent: " + message);
    wss.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(message);
        }
    })
}

// Starts the websocket server
server.listen(port_message, function() {
    console.log(`Server is listening on ${port_message}!`)
})
  
console.log('Server started at http://localhost:' + port_message);


/* -------------------------------------------
    Here we serve the html to client
--------------------------------------------*/

// Static Files
app.use(express.static('public'));

// Navigation
app.get('', (req, res) => {
    res.render('index')
})

app.listen(port_web, () => console.info(`App listening on port ${port_web}`))
console.log('Server started at http://localhost:' + port_web);

/* -------------------------------------------
    Check shared memory
--------------------------------------------*/
const send_queue = [];

function write_shared_memory(message) {
    var buf = Buffer.from(message);
    shm.write(buf);
    // res.send(shm.read());
}

function read_shared_memory() {
    return shm.read();
}

var old_message = "";
function check_mem() {
    message = read_shared_memory();

    
    //message = read_shared_memory();
    if (message != old_message) {
        if(message != ""){ send_message(message); }

        var to_send = "";
        if(send_queue.length){
            to_send = send_queue.shift();
        }
        write_shared_memory(to_send);
        old_message = to_send
    }
}

write_shared_memory("test message from shared mem and server");
var id = setInterval(check_mem, 200); // check every 500ms
