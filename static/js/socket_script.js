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

    function buttonStopAudio() {
       clearInterval(audio_Interval);
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




  var socket = io.connect('http://localhost:5000/gui');

  socket.on('connect', function() {
      console.log('gui is connected');
  });

  socket.on('audio_command', function(msg) {
      $('#audio_command').text(msg.data.data); // assuming only one command at a time
      console.log('Starting audio watch');
      buttonStartAudio();
  });

  socket.on('audio_executed', function() {
      console.log('Stopping audio watch');
      buttonResetAudio();
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
