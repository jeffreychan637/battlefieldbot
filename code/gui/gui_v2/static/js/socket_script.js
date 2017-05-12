$(document).ready(function() {

  var progressCtx = $("#progress-chart")[0].getContext('2d');
  var xOffsetCtx = $("#x-offset-chart")[0].getContext('2d');
  var distanceCtx = $("#distance-chart")[0].getContext('2d');
  var sonarDistCtx = $("#sonar-dist-chart")[0].getContext('2d');

  //Could have chart on how close an object got

  // var gradient = ctx.createLinearGradient(0, 0, 0, 400);
  // gradient.addColorStop(0, 'rgba(250,174,50,1)');
  // gradient.addColorStop(1, 'rgba(250,174,50,0)');

  // var gradient2 = ctx.createLinearGradient(0, 0, 400, 0);
  // gradient2.addColorStop(0, 'rgba(174,250,50,1)');
  // gradient2.addColorStop(1, 'rgba(174,50,250,1)');

  // var xs = ["0","1","2"];
  // var ys = [0.0,3.0,4.0];

  var endX;
  var endY;

  var fillBetweenLinesPlugin = {
    afterDatasetsDraw: function (chart) {
        var ctx = chart.chart.ctx;
        var xaxis = chart.scales['x-axis-0'];
        var yaxis = chart.scales['y-axis-0'];
        var datasets = chart.data.datasets;
        ctx.save();

        for (var d = 0; d < datasets.length; d++) {
            var dataset = datasets[d];
            if (dataset.fillBetweenSet == undefined) {
                continue;
            }

            // get meta for both data sets
            var meta1 = chart.getDatasetMeta(d);
            var meta2 = chart.getDatasetMeta(dataset.fillBetweenSet);

            ctx.beginPath();

            // vars for tracing
            var curr, prev;

            // trace set1 line
            for (var i = 0; i < meta1.data.length; i++) {
                curr = meta1.data[i];
                if (i === 0) {
                    ctx.moveTo(curr._view.x, curr._view.y);
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }
                if (curr._view.steppedLine === true) {
                    ctx.lineTo(curr._view.x, prev._view.y);
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }
                if (curr._view.tension === 0) {
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }

                ctx.bezierCurveTo(
                  prev._view.controlPointNextX,
                  prev._view.controlPointNextY,
                  curr._view.controlPointPreviousX,
                  curr._view.controlPointPreviousY,
                  curr._view.x,
                  curr._view.y
                );
                prev = curr;
            }


            // connect set1 to set2 then BACKWORDS trace set2 line
            for (var i = meta2.data.length - 1; i >= 0; i--) {
                curr = meta2.data[i];
                if (i === meta2.data.length - 1) {
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }
                if (curr._view.steppedLine === true) {
                    ctx.lineTo(prev._view.x, curr._view.y);
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }
                if (curr._view.tension === 0) {
                    ctx.lineTo(curr._view.x, curr._view.y);
                    prev = curr;
                    continue;
                }

                // reverse bezier
                ctx.bezierCurveTo(
                  prev._view.controlPointPreviousX,
                  prev._view.controlPointPreviousY,
                  curr._view.controlPointNextX,
                  curr._view.controlPointNextY,
                  curr._view.x,
                  curr._view.y
                );
                prev = curr;
            }

            ctx.closePath();
            ctx.fillStyle = dataset.fillBetweenColor || "rgba(0,0,0,0.1)";
            ctx.fill();
        }
    } // end afterDatasetsDraw
}; // end fillBetweenLinesPlugin

Chart.pluginService.register(fillBetweenLinesPlugin);

  // var chart = AmCharts.makeChart("chartdiv", {
  //     "type": "serial",
  //     "theme": "light",
  //     "marginRight":80,
  //     "marginTop":24,
  //     "dataDateFormat":"YYYY-MM-DD",
  //     "rotate": true,
  //     "dataProvider": [{
  //         "date": "2013-11-30",
  //         "value": 104
  //     }, {
  //         "date": "2013-12-01",
  //         "value": 108
  //     }, {
  //         "date": "2013-12-02",
  //         "value": 103
  //     }, {
  //         "date": "2013-12-03",
  //         "value": 105
  //     }, {
  //         "date": "2013-12-04",
  //         "value": 136
  //     }, {
  //         "date": "2013-12-05",
  //         "value": 138
  //     }, {
  //         "date": "2013-12-06",
  //         "value": 113
  //     }, {
  //         "date": "2013-12-07",
  //         "value": 131
  //     }, {
  //         "date": "2013-12-08",
  //         "value": 114
  //     }, {
  //         "date": "2013-12-09",
  //         "value": 124
  //     }],
  //     "valueAxes": [{
  //         "maximum": 140,
  //         "minimum": 100,
  //         "axisAlpha": 0,
  //         "guides": [{
  //             "fillAlpha": 0.1,
  //             "fillColor": "#99dc67",
  //             "lineAlpha": 0,
  //             "toValue": 120,
  //             "value": 0
  //         }, {
  //             "fillAlpha": 0.1,
  //             "fillColor": "#67b7dc",
  //             "lineAlpha": 0,
  //             "toValue": 200,
  //             "value": 120
  //         }]
  //     }],
  //     "graphs": [{
  //         "bullet": "round",
  //         "dashLength": 4,
  //         "valueField": "value"
  //     }],
  //     "chartCursor": {
  //         "cursorAlpha": 0,
  //         "categoryBalloonEnabled": false
  //     },
  //     "categoryField": "date",
  //     "categoryAxis": {
  //         "parseDates": true
  //     },
  //     "chartScrollbar":{
  //         "scrollbarHeight":5,
  //         "backgroundAlpha":0.1,
  //         "backgroundColor":"#868686",
  //         "selectedBackgroundColor":"#67b7dc",
  //         "selectedBackgroundAlpha":1
  //     },
  //     "export": {
  //         "enabled": true
  //      }
  // });

  var progressConfig = {
    type: 'line',
    data: {
      datasets: [{
            label: 'Projected',
            borderColor: '#0f6e42',
            pointBackgroundColor: '#094227',
            backgroundColor: '#6fa88d',
            fill: false,
            data: [{
                  x: 0,
                  y: 0
              }]

          }, {
            label: 'Progress',
            borderColor: '#428bca',
            pointBackgroundColor: '#357ebd',
            fill: false,
            fillBetweenSet: 0,
            fillBetweenColor: "rgba(160,197,228,0.4)",
            backgroundColor: '#a0c5e4',
            data: []
          }],
    },
    options: {
      scales: {
              xAxes: [{
                  type: 'linear',
                  position: 'bottom'
              }]
          }
    }
  }

  var xOffsetConfig = {
    type: 'line',
    data: {
      datasets: [{
            label: 'Projected',
            borderColor: '#977FFA',
            pointBackgroundColor: '#977FFA',
            backgroundColor: '#c0b2fc',
            fill: false,
            data: [{
                  x: 0,
                  y: 0
              }]

          }, {
            label: 'X Offset',
            borderColor: '#5496cf',
            pointBackgroundColor: '#5496cf',
            fill: false,
            fillBetweenSet: 0,
            fillBetweenColor: "rgba(152,192,226,0.4)",
            backgroundColor: '#98c0e2',
            data: []
          }],
    },
    options: {
      scales: {
              xAxes: [{
                  type: 'linear',
                  position: 'bottom'
              }]
          }
    }
  }

  var distanceConfig = {
    type: 'line',
    data: {
      datasets: [{
            label: 'Distance Remaining',
            borderColor: '#EF8403',
            pointBackgroundColor: '#EF8403',
            fill: false,
            backgroundColor: '#f5b567',
            data: []
          }],
    },
    options: {
      scales: {
              xAxes: [{
                  type: 'linear',
                  position: 'bottom',
                  scaleLabel: {
                    display: true,
                    labelString: 'Time (seconds)',
                  }
              }]
          }
    }
  }

  var sonarDistConfig = {
    type: 'line',
    data: {
      datasets: [{
            label: 'Detect Object Distance',
            pointBackgroundColor: '#e94f59',
            backgroundColor: '#e94f59',
            fill: false,
            showLine: false,
            data: [],
          }],
    },
    options: {
      scales: {
              xAxes: [{
                  type: 'linear',
                  position: 'bottom',
                  scaleLabel: {
                    display: true,
                    labelString: 'Time (seconds)',
                  }
              }]
          }
    }
  }

// var config = {
//   type: 'line',
//   data: {
//     labels: xs,
//     datasets: [{
//       label: "Movements",
//       data: ys,
//       fill: true,
//       borderColor: gradient2,
//       backgroundColor: gradient
//     }]
//   },
//   options: {
//     legend: {
//       display: true
//     },
//     tooltips: {
//       callbacks: {
//         label: function(tooltipItem) {
//           return tooltipItem.yLabel;
//         }
//       }
//     },
//     scales:
//         {
//             xAxes: [{
//                 ticks: {
//                   max: endX,
//                   min: -5,
//                   stepSize: 1
//                 }
//             }],
//             yAxes: [{
//                 ticks: {
//                     max: endY,
//                     min: -endY,
//                     stepSize: 1
//                 }
//             }]
//         }
//   }
// };

  function graph() {
    new Chart(progressCtx, progressConfig);
    new Chart(xOffsetCtx, xOffsetConfig);
    new Chart(distanceCtx, distanceConfig);
    new Chart(sonarDistCtx, sonarDistConfig);
  }

  function getExpectedX(currY) {
    return (endX * currY) / (1.0 * endY)
  }

  function setXOffsetGraph(currX, currY) {
    xOffset = getExpectedX(currY) - currX
    xOffsetConfig.data.datasets[1].data.push({x: currY, y: xOffset})
  }

  function getTimeDiff() {
    return ((new Date().getTime()) - originalTime) / 1000;
  }

  function getDistance(currX, currY) {
    xDiff = endX - currX;
    yDiff = endY - currY;
    return Math.sqrt((xDiff ** 2) + (yDiff ** 2))
  }

  function setDistanceGraph(currX, currY) {
    distance = getDistance(currX, currY);
    time = getTimeDiff();
    distanceConfig.data.datasets[0].data.push({x: time, y: distance});
  }

  var socket = io.connect('http://localhost:5000/gui');

  var originalTime = new Date().getTime();

  socket.on('connect', function() {
      console.log('gui is connected');
  });

  socket.on('sonar_dist', function(msg) {
      console.log(msg.data);
      $('#sonar_dist').text(msg.data).css("color", "red");
      sonarDistConfig.data.datasets[0].data.push({x : getTimeDiff(), y : msg.data});
  });

  socket.on('state', function(msg) {
      console.log(msg.data);
      new_state = msg.data.toUpperCase();
      $('#state').text(new_state);
      if (new_state != "AVOIDANCE") {
        $('#sonar_dist').text("CLEAR").css("color", "green");
      }
      if (new_state == "INIT") {
        $('#state').css("color", "blue");
      } else if (new_state == "NORMAL") {
        $('#state').css("color", "green");
      } else if (new_state == "GOAL") {
        $('#state').css("color", "#FFD700");
      } else {
        $('#state').css("color", "red");
      }
  });

  socket.on('curr', function(msg) {
      console.log(msg.data);
      $('#curr').text(msg.data);
      x = msg.data.split(",")[0].slice(1);
      y = msg.data.split(",")[1].slice(0, -1);
      progressConfig.data.datasets[1].data.push({x : x, y : y});
      setXOffsetGraph(x, y);
      setDistanceGraph(x, y);
      // xs.push(x);
      // ys.push(parseInt(y));
      graph();
  });

  socket.on('dest', function(msg) {
    console.log(msg.data);
      $('#dest').text(msg.data);
      endX = msg.data.split(",")[0].slice(1);
      endY = msg.data.split(",")[1].slice(0, -1);
      console.log(endX);
      console.log(endY);
      progressConfig.data.datasets[0].data.push({x : endX, y : endY});
      xOffsetConfig.data.datasets[0].data.push({x : endY, y : 0});
      graph();
  });

  socket.on('accel_X', function(msg) {
    console.log(msg.data);
      $('#accel_X').text(msg.data);
  });

  socket.on('accel_Y', function(msg) {
    console.log(msg.data);
      $('#accel_Y').text(msg.data);
  });

  graph();

    // socket.on('sonar_dist', function(msg) {
    //     $('#log').append('<br>' + $('<div/>').text('Received #' + msg.count + ': ' + msg.data).html());
    // });
});
