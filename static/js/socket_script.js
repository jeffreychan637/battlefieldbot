$(document).ready(function() {
  var audio_seconds = 00;
  var audio_tens = 00;
  var audio_appendTens = document.getElementById("audio_tens")
  var audio_appendSeconds = document.getElementById("audio_seconds")
  var audio_Interval;

  function buttonStartAudio() {
     clearInterval(audio_Interval);
     audio_Interval = setInterval(startTimerAudio, 10);
  }

  function buttonResetAudio() {
     clearInterval(audio_Interval);
    audio_seconds = '00';
    audio_tens = '00';
    audio_appendTens.innerHTML = audio_tens;
    audio_appendSeconds.innerHTML = audio_seconds;
  }

  function startTimerAudio() {
    audio_tens++;
    if(audio_tens < 9){
      audio_appendTens.innerHTML = "0" + audio_tens;
    }
    if (audio_tens > 9){
      audio_appendTens.innerHTML = audio_tens;
    }
    if (audio_tens > 99) {
      audio_seconds++;
      audio_appendSeconds.innerHTML = "0" + audio_seconds;
      audio_tens = 0;
      audio_appendTens.innerHTML = "0" + 0;
    }
    if (audio_seconds > 9){
      audio_appendSeconds.innerHTML = audio_seconds;
    }
  }

  var v_image_seconds = 00;
  var v_image_tens = 00;
  var v_image_appendTens = document.getElementById("v_image_tens");
  var v_image_appendSeconds = document.getElementById("v_image_seconds");
  var v_image_Interval;

  function buttonStartVImage() {
     clearInterval(v_image_Interval);
     v_image_Interval = setInterval(startTimerVImage, 10);
  }

  function buttonResetVImage() {
     clearInterval(v_image_Interval);
    v_image_tens = "00";
    v_image_seconds = "00";
    v_image_appendTens.innerHTML = v_image_tens;
    v_image_appendSeconds.innerHTML = v_image_seconds;
  }

  function startTimerVImage() {
    v_image_tens++;

    if(v_image_tens < 9){
      v_image_appendTens.innerHTML = "0" + v_image_tens;
    }

    if (v_image_tens > 9){
      v_image_appendTens.innerHTML = v_image_tens;

    }

    if (v_image_tens > 99) {
      v_image_seconds++;
      v_image_appendSeconds.innerHTML = "0" + v_image_seconds;
      v_image_tens = 0;
      v_image_appendTens.innerHTML = "0" + 0;
    }

    if (v_image_seconds > 9){
      v_image_appendSeconds.innerHTML = v_image_seconds;
    }

  }


  var v_exec_seconds = 00;
  var v_exec_tens = 00;
  var v_exec_appendTens = document.getElementById("v_exec_tens");
  var v_exec_appendSeconds = document.getElementById("v_exec_seconds");
  var v_exec_Interval;

  function buttonStartVExec() {
     clearInterval(v_exec_Interval);
     v_exec_Interval = setInterval(startTimerVExec, 10);
  }

  function buttonResetVExec() {
     clearInterval(v_exec_Interval);
    v_exec_tens = "00";
    v_exec_seconds = "00";
    v_exec_appendTens.innerHTML = v_exec_tens;
    v_exec_appendSeconds.innerHTML = v_exec_seconds;
  }

  function startTimerVExec() {
    v_exec_tens++;

    if(v_exec_tens < 9){
      v_exec_appendTens.innerHTML = "0" + v_exec_tens;
    }

    if (v_exec_tens > 9){
      v_exec_appendTens.innerHTML = v_exec_tens;

    }

    if (v_exec_tens > 99) {
      v_exec_seconds++;
      v_exec_appendSeconds.innerHTML = "0" + v_exec_seconds;
      v_exec_tens = 0;
      v_exec_appendTens.innerHTML = "0" + 0;
    }

    if (v_exec_seconds > 9){
      v_exec_appendSeconds.innerHTML = v_exec_seconds;
    }

  }




  var socket = io.connect('http://localhost:5000/gui');

  socket.on('connect', function() {
      console.log('gui is connected');
  });

  socket.on('audio_command', function(msg) {
      $('#audio_command').text(msg.data.data); // assuming only one command at a time
      console.log('Starting audio watch');
      // buttonStartAudio();
      // buttonStartVImage();
      buttonStartVExec();
  });

  socket.on('audio_executed', function() {
      console.log('Stopping audio watch');
      // buttonResetAudio();
      // buttonResetVImage();
      buttonResetVExec();
  });

    // socket.on('audio_command', function(msg) {
    //     $('#log').append('<br>' + $('<div/>').text('Received #' + msg.count + ': ' + msg.data).html());
    // });

    var ping_pong_times = [];
    var start_time;
    window.setInterval(function() {
        start_time = (new Date).getTime();
        socket.emit('my_ping');
    }, 1000);

    socket.on('my_pong', function() {
        var latency = (new Date).getTime() - start_time;
        ping_pong_times.push(latency);
        ping_pong_times = ping_pong_times.slice(-30); // keep last 30 samples
        var sum = 0;
        for (var i = 0; i < ping_pong_times.length; i++)
            sum += ping_pong_times[i];
        $('#ping-pong').text(Math.round(10 * sum / ping_pong_times.length) / 10);
    });
});
