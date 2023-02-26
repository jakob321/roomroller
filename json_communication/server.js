const fs = require('fs')

fs.watchFile('abc.json', {interval: 500}, (curr, prev) => {
    console.log('updated file: '+ curr.toString());
  });

console.log('hello world');