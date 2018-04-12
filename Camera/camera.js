mergeInto(LibraryManager.library, {

    wa_initiateCamera: function (htmlVideoId, width, height) {
        'use strict'

        
        console.log(Pointer_stringify(htmlVideoId))

        let videoElement = document.getElementById(Pointer_stringify(htmlVideoId))

        console.log(videoElement)

        let constraints = {
            audio: false,
            video: {
                width: width,
                height: height,
            }
        }

        if(navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
            // Not adding `{ audio: true }` since we only want video now
            navigator.mediaDevices.getUserMedia(constraints).then(function(stream) {
                videoElement.srcObject = stream;
                videoElement.play();
                console.log("video now playing")
            }).catch((err) => {
                console.log("error getting camera: ", err)
            })
        }

    },

});