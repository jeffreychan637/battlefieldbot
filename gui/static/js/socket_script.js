$(document).ready(function() {
  var image_count = 0;
  var links = [];

  function add_image() {
      links.push('static/images/img_' + image_count.toString() + '.jpg');
      $('<div class="item"><img src="'+links[image_count]+'"><div class="carousel-caption"></div>   </div>').appendTo('.carousel-inner');
      $('<li data-target="#carousel_image" data-slide-to="'+image_count+'"></li>').appendTo('.carousel-indicators');

      $('.item').first().removeClass('active');
      $('.carousel-indicators > li').first().removeClass('active');
      $('.item').last().addClass('active');
      $('.carousel-indicators > li').last().addClass('active');
      image_count++;
  }


  ////////////////////////////////////////////////////////////

  var angle_data = [30, 330];
  var angle_ctx = $("#angle")[0].getContext('2d');

  function graphPie() {
    var sample = {
      labels: [
          "Angle",
          "Bg"
      ],
      datasets: [
          {
              data: angle_data,
              backgroundColor: [
                  "#FF6384",
                  "#FFFFFF"
              ]
      }]
    };

    var angle_cfg = {
        type: 'pie',
        data: sample,
        options: {
          legend: {
            display: false
          },
          tooltips: {
            enabled: false
          }
        }
    };
    
    new Chart(angle_ctx, angle_cfg);
  }

  graphPie();

////////////////////////////////////////////////////////////

  var audio_seconds = 00;
  var audio_tens = 00;
  var audio_appendTens = document.getElementById("audio_tens")
  var audio_appendSeconds = document.getElementById("audio_seconds")
  var audio_Interval;
  var times = [];
  var labels = [];
  var count = 0;

  function buttonStartAudio() {
     clearInterval(audio_Interval);
     audio_Interval = setInterval(startTimerAudio, 10);
  }

  function buttonResetAudio() {
    times.push(audio_seconds + (audio_tens / 100.0));
    labels.push(count.toString());
    console.log(times);
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

  ////////////////////////////////////////////////////////////

  var v_exec_seconds = 00;
  var v_exec_tens = 00;
  var v_exec_appendTens = document.getElementById("v_exec_tens");
  var v_exec_appendSeconds = document.getElementById("v_exec_seconds");
  var v_exec_Interval;
  var times2 = [];
  var labels2 = [];
  var count2 = 0;

  function buttonStartVExec() {
     clearInterval(v_exec_Interval);
     v_exec_Interval = setInterval(startTimerVExec, 10);
  }

  function buttonResetVExec() {
    times2.push(v_exec_seconds + (v_exec_tens / 100.0));
    labels2.push(count2.toString());
    console.log(times2);
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

  ////////////////////////////////////////////////////////////

  var v_image_seconds = 00;
  var v_image_tens = 00;
  var v_image_appendTens = document.getElementById("v_image_tens");
  var v_image_appendSeconds = document.getElementById("v_image_seconds");
  var v_image_Interval;
  var times3 = [];
  var labels3 = [];
  var count3 = 0;

  function buttonStartVImage() {
     clearInterval(v_image_Interval);
     v_image_Interval = setInterval(startTimerVImage, 10);
  }

  function buttonResetVImage() {
    times3.push(v_image_seconds + (v_image_tens / 100.0));
    labels3.push(count3.toString());
    console.log(times3);
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

  ////////////////////////////////////////////////////////////

  var progintervalAudio;
  var maxAudio = 30000;
  var incrementAudio = maxAudio / 100.0;
  var currPercAudio = 0;

  function startProgressAudio() {
    clearInterval(progintervalAudio);
    progintervalAudio = setInterval(animateProgressAudio, incrementAudio);
  }

  function animateProgressAudio() {
    currPercAudio++;
    $('#progress_audio').attr('aria-valuenow', currPercAudio.toString()).css('width',currPercAudio.toString() + "%");
    $('#progress_audio_num').text(currPercAudio.toString() + "%");
  }

  function resetProgressAudio() {
    clearInterval(progintervalAudio);
    currPercAudio = 0;
    $('#progress_audio').attr('aria-valuenow', currPercAudio.toString()).css('width',currPercAudio.toString() + "%");
    $('#progress_audio_num').text(currPercAudio.toString() + "%");
  }

  ////////////////////////////////////////////////////////////

  var progintervalVisualExec;
  var maxVisualExec = 26000;
  var incrementVisualExec = maxVisualExec / 100.0;
  var currPercVisualExec = 0;

  function startProgressVisualExec() {
    clearInterval(progintervalVisualExec);
    progintervalVisualExec = setInterval(animateProgressVisualExec, incrementVisualExec);
  }

  function animateProgressVisualExec() {
    currPercVisualExec++;
    $('#progress_visual_exec').attr('aria-valuenow', currPercVisualExec.toString()).css('width',currPercVisualExec.toString() + "%");
    $('#progress_visual_exec_num').text(currPercVisualExec.toString() + "%");
  }

  function resetProgressVisualExec() {
    clearInterval(progintervalVisualExec);
    currPercVisualExec = 0;
    $('#progress_visual_exec').attr('aria-valuenow', currPercVisualExec.toString()).css('width',currPercVisualExec.toString() + "%");
    $('#progress_visual_exec_num').text(currPercVisualExec.toString() + "%");
  }

  ////////////////////////////////////////////////////////////

  var progintervalVisualImage;
  var maxVisualImage = 28000;
  var incrementVisualImage = maxVisualImage / 100.0;
  var currPercVisualImage = 0;

  function startProgressVisualImage() {
    clearInterval(progintervalVisualImage);
    progintervalVisualImage = setInterval(animateProgressVisualImage, incrementVisualImage);
  }

  function animateProgressVisualImage() {
    currPercVisualImage++;
    $('#progress_visual_image').attr('aria-valuenow', currPercVisualImage.toString()).css('width',currPercVisualImage.toString() + "%");
    $('#progress_visual_image_num').text(currPercVisualImage.toString() + "%");
  }

  function resetProgressVisualImage() {
    clearInterval(progintervalVisualImage);
    currPercVisualImage = 0;
    $('#progress_audio').attr('aria-valuenow', currPercVisualImage.toString()).css('width',currPercVisualImage.toString() + "%");
    $('#progress_audio_num').text(currPercVisualImage.toString() + "%");
  }

////////////////////////////////////////////////////////////

var ctx = $("#chart")[0].getContext('2d');

var gradient = ctx.createLinearGradient(0, 0, 0, 400);
gradient.addColorStop(0, 'rgba(250,174,50,1)');
gradient.addColorStop(1, 'rgba(250,174,50,0)');

var gradient2 = ctx.createLinearGradient(0, 0, 400, 0);
gradient2.addColorStop(0, 'rgba(174,250,50,1)');
gradient2.addColorStop(1, 'rgba(174,50,250,1)');


var config = {
  type: 'line',
  data: {
    labels: labels,
    datasets: [{
      label: "Audio Exec Times",
      data: times,
      fill: true,
      borderColor: gradient2,
      backgroundColor: gradient
    }]
  },
  options: {
    legend: {
      display: true
    },
    tooltips: {
      callbacks: {
        label: function(tooltipItem) {
        console.log(tooltipItem)
          return tooltipItem.yLabel;
        }
      }
    },
    scales:
        {
            xAxes: [{
                display: false
            }],
            yAxes: [{
                ticks: {
                    max: maxAudio / 1000,
                    min: 0,
                    stepSize: (maxAudio / 1000) / ((maxAudio / 1000) / 2.0)
                }
            }]
        }
  }
};

function graph() {
  new Chart(ctx, config);
}

////////////////////////////////////////////////////////////

var ctx2 = $("#chart2")[0].getContext('2d');

var config2 = {
  type: 'line',
  data: {
    labels: labels2,
    datasets: [{
      label: "Visual Exec Times",
      data: times2,
      fill: true,
      borderColor: gradient2,
      backgroundColor: gradient
    }]
  },
  options: {
    legend: {
      display: true
    },
    tooltips: {
      callbacks: {
        label: function(tooltipItem) {
        console.log(tooltipItem)
          return tooltipItem.yLabel;
        }
      }
    },
    scales:
        {
            xAxes: [{
                display: false
            }],
            yAxes: [{
                ticks: {
                    max: maxVisualExec / 1000,
                    min: 0,
                    stepSize: (maxAudio / 1000) / ((maxAudio / 1000) / 2.0)
                }
            }]
        }
  }
};

function graph2() {
  new Chart(ctx2, config2);
}

////////////////////////////////////////////////////////////

var ctx3 = $("#chart3")[0].getContext('2d');

var config3 = {
  type: 'line',
  data: {
    labels: labels3,
    datasets: [{
      label: "Visual Image Times",
      data: times3,
      fill: true,
      borderColor: gradient2,
      backgroundColor: gradient
    }]
  },
  options: {
    legend: {
      display: true
    },
    tooltips: {
      callbacks: {
        label: function(tooltipItem) {
        console.log(tooltipItem)
          return tooltipItem.yLabel;
        }
      }
    },
    scales:
        {
            xAxes: [{
                display: false
            }],
            yAxes: [{
                ticks: {
                    max: maxVisualImage / 1000,
                    min: 0,
                    stepSize: (maxAudio / 1000) / ((maxAudio / 1000) / 2.0)
                }
            }]
        }
  }
};

function graph3() {
  new Chart(ctx3, config3);
}

////////////////////////////////////////////////////////////

  var socket = io.connect('http://localhost:5000/gui');

  socket.on('connect', function() {
      console.log('gui is connected');
  });

  socket.on('audio_command', function(msg) {
    console.log(msg.data);
      $('#audio_command').text(msg.data.toUpperCase()); // assuming only one command at a time
      console.log('Starting audio watch');
      buttonStartAudio();
      startProgressAudio();
      graph();
  });

  socket.on('audio_executed', function() {
      console.log('Stopping audio watch');
      buttonResetAudio();
      resetProgressAudio();
      graph();
  });

  socket.on('visual_info', function(msg) {
      var size_target = msg.size_target;
      $('#size_target_class').removeClass('p50').addClass('p' + size_target);
      $('#size_target_num').text(size_target + '%');

      var center = msg.center;
      $('#center').text(center);

      var angle = msg.angle;
      angle_data = [parseInt(angle), 360-parseInt(angle)];
      graphPie();
      $('#angle_degrees').text(angle + " Degrees");

      console.log('Starting visual exec watch');
      buttonStartVExec();
      startProgressVisualExec();
      graph2();
  });

  socket.on('visual_executed', function() {
      console.log('Stopping visual exec watch');
      buttonResetVExec();
      resetProgressVisualExec();
      graph2();
  });

  var visual_image_started = false;
  socket.on('visual_image_received', function() {
      console.log('Visual image received');
      add_image();

      if (visual_image_started) {
        buttonResetVImage();
        resetProgressVisualImage();
        buttonStartVImage();
        startProgressVisualImage();
        graph3();
      }
      else {
        buttonStartVImage();
        startProgressVisualImage();
        graph3();
        visual_image_started = true;
      }
  });


    // socket.on('audio_command', function(msg) {
    //     $('#log').append('<br>' + $('<div/>').text('Received #' + msg.count + ': ' + msg.data).html());
    // });
});
