const video = document.querySelector("video");
const canvas = document.querySelector("canvas");
const c = canvas.getContext("2d");

const faceMinSizeSlider = document.querySelector("#faceMinSize");
const REQUIRED_ACCURACY = 0.95;

let model = null;
let enableFaceDetection = false;
let faceMinSize = 1; // Minimal size of the face to trigger a switch in pixels
let lastSighting = 0; // Last time a face was seen
let switchOffDelay = 5000; // After how many ms with no sighting should we switch off?
let stateA = false; // Current state of the power outlet


async function main() {
    if (!supportsWebcam()) {
        alert("Your browser does not support webcam capture. Please use a different browser or update your current one.");
    }


    model = await blazeface.load();

    video.addEventListener("loadeddata", function() {
        canvas.width = video.getBoundingClientRect().width;
        canvas.height = video.getBoundingClientRect().height;

        faceMinSize.max = Math.max(canvas.width, canvas.height);
        
        mainLoop();
    });
}

function supportsWebcam() {
    return !!(navigator.mediaDevices && navigator.mediaDevices.getUserMedia);
}

function startCapture() {
    navigator.mediaDevices.getUserMedia({ video: true }).then((stream) => {
        video.srcObject = stream;
    });
}

async function mainLoop() {
    let predictions = await model.estimateFaces(video, false);

    c.clearRect(0, 0, canvas.width, canvas.height);
    if (predictions.length > 0) {

        for (let pred of predictions) {
            if (pred.probability < REQUIRED_ACCURACY) continue;
            let x = pred.topLeft[0];
            let y = pred.topLeft[1];
            let width = pred.bottomRight[0] - x;
            let height = pred.bottomRight[1] - y;
            c.strokeStyle = 'green';
            c.lineWidth = 2;

            if (width > faceMinSize) {
                c.strokeStyle = 'red';
                lastSighting = Date.now();
                switchOn();
            }

            c.strokeRect(x, y, width, height);
        }

    }
    
    // If last sighting was more than 5s ago, turn off the outlet
    if (Date.now() - lastSighting > switchOffDelay) {
        switchOff();
    }

    if (enableFaceDetection) {
        setTimeout(mainLoop, 50);
    }

}

main();

/******* FORM INPUT **********/
function checkFaceDetection(e) {
    enableFaceDetection = e.target.checked;
    
    if (enableFaceDetection) {
        startCapture();
    }
}

function setFaceMinSize(e) {
    faceMinSize = Number(faceMinSizeSlider.value);
}

function setSwitchOffDelay(e) {
    switchOffDelay = Number(e.target.value);
}

function switchOn() {
    if(stateA)
        return;

    // Fire and forget
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "https://192.168.0.113/switch/a/on", false);
    //xhr.send();
    console.log("ON");

    stateA = true;
}

function switchOff() {
    if(!stateA)
        return;

    // Fire and forget
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "https://192.168.0.113/switch/a/off", false);
    //xhr.send();
    console.log("OFF");

    stateA = false;
}
