mergeInto(LibraryManager.library, {

    createCamera: function (status, width, height) {
        'use strict'

        var rootElement = document.documentElement;

        console.log('Creating video')
        
        const video = document.createElement('VIDEO')
        video.id = "mathworks-camera-video"
        video.style.visibility = "hidden"
        rootElement.appendChild(video)

        console.log('Creating canvas')

        const canvas = document.createElement('CANVAS')
        canvas.id = "mathworks-camera-canvas"
        canvas.style.visibility = "hidden"
        canvas.width = width
        canvas.height = height
        rootElement.appendChild(canvas)


        const constraints = {
            audio: true,
            video: { width: width, height: height }
        }

        const context = canvas.getContext('2d')

        navigator.mediaDevices.getUserMedia(constraints)
            .then(function (mediaStream) {

                video.srcObject = mediaStream
                video.onloadedmetadata = function (e) {                    
                    video.play()
                    setValue(status, 1, 'i32')     // Acknoledge camera stream access
                }

            })
            .catch(function (err) {
                /* handle the error */
                setValue(status, -1, 'i32')    // Acknoledge camera stream failure
            })
    },

    getCameraImage: function (imageData, width, height) {

        const video = document.getElementById("mathworks-camera-video")        
        const canvas = document.createElement("mathworks-camera-canvas")
        const context = canvas.getContext('2d')

        context.drawImage(this.video, 0, 0, width, height);
        imageData = context.getImageData(0, 0, width, height);
    }


});