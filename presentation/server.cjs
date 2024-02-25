
const http2 = require('http2');
const fs = require('fs');
const path = require('path');
const mime = require('mime-types');

const {
    HTTP2_HEADER_PATH,
    HTTP2_HEADER_METHOD,
    HTTP_STATUS_NOT_FOUND,
    HTTP_STATUS_INTERNAL_SERVER_ERROR
} = http2.constants;


const server = http2.createSecureServer({
    key: fs.readFileSync('localhost-privkey.pem'),
    cert: fs.readFileSync('localhost-cert.pem'),
});

const serverRoot = "./dist";

function respondToStreamError(err, stream) {
    console.log(err);
    if (err.code === 'ENOENT') {
        stream.respond({ ":status": HTTP_STATUS_NOT_FOUND });
    } else {
        stream.respond({ ":status": HTTP_STATUS_INTERNAL_SERVER_ERROR });
    }
    stream.end();
}

function getPathFromUrl(url) {
    return url.split("?")[0];
}

server.on('stream', (stream, headers) => {
    const reqPath = headers[HTTP2_HEADER_PATH];
    const reqMethod = headers[HTTP2_HEADER_METHOD];
    let fullPath = path.join(serverRoot, getPathFromUrl(reqPath));
    const responseMimeType = mime.lookup(fullPath);
    const exists = fs.existsSync(fullPath)
    if (!exists){
        fullPath="dist/index.html"
    }
    console.log(`${new Date()} ${fullPath}`)
    stream.respondWithFile(fullPath, {
        'content-type': responseMimeType,
        'Cache-Control':'max-age=604800'
    }, {
        onError: (err) => respondToStreamError(err, stream)
    });


});

server.listen(8080);