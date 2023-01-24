const output = document.querySelector('.output');

//uncomment the next if you want this code to fetch without adding products. 
//const url = "https://script.google.com/macros/s/AKfycbz8rV5i0_idjKC86kr60wR-rOaM4ha5ZsPYIPvbCiqf1piaOsYNS-lOfvk8LpvI8VB21Q/exec";

//uncomment the next if you want this code to fetch and add new product at the same time. 
const url = "https://script.google.com/macros/s/AKfycbyQsK-k0H7rbzWgBlFv35QIZjwcc7XhDwopLFOKLaL_J9-lMNe8f1yqSJ27TL7BCpj3/exec";
//document.addEventListener('DOMContentLoaded', init);
var temperature = [3];
var humidity = [4];
var soil_moisture = [5];
var soilpH = [6];
var uV = [7];
var xValues = [0,];


setInterval(() => {
    fetch(url)
        .then(res => res.json())
        .then(data => {
            for (i = 1; i < data.length; i++) {
                temperature.push(data[i].temperature);
                humidity.push(data[i].humidity);
                soil_moisture.push(data[i].soil_moisture);
                soilpH.push(data[i].soilpH);
                uV.push(data[i].uV);
                xValues.push(data[i].timee);
            }
            init()
        });
}, 5000);

function init() {
    new Chart("Chart1", {
        type: "line",
        data: {
            labels: xValues.slice(xValues.length - 10),
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgb(255,33,79,0.2)",
                pointBackgroundColor: "rgb(255,33,79)",
                data:temperature.slice(temperature.length - 10)
            }]
        },
        options: {
            legend: { display: false },
            scales: {
                yAxes: [{ ticks: { min: 0, max: 80 } }],
            },
            animation: {
                duration: 0
            },
            elements: {
                point :{
                    radius: 5,
                }
                
            }
        }
        
    });
    new Chart("Chart2", {
        type: "line",
        data: {
            labels: xValues.slice(xValues.length - 10),
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgb(255,33,79,0.2)",
                pointBackgroundColor: "rgb(255,33,79)",
                data:humidity.slice(humidity.length - 10)
            }]
        },
        options: {
            legend: { display: false },
            scales: {
                yAxes: [{ ticks: { min: 0, max: 100 } }],
            },
            animation: {
                duration: 0
            },
            elements: {
                point :{
                    radius: 5,
                }
                
            }
        }
        
    });
    new Chart("Chart3", {
        type: "line",
        data: {
            labels: xValues.slice(xValues.length - 10),
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgb(255,33,79,0.2)",
                pointBackgroundColor: "rgb(255,33,79)",
                data:soil_moisture.slice(soil_moisture.length - 10)
            }]
        },
        options: {
            legend: { display: false },
            scales: {
                yAxes: [{ ticks: { min: 0, max: 100 } }],
            },
            animation: {
                duration: 0
            },
            elements: {
                point :{
                    radius: 5,
                }
                
            }
        }
        
    });
    new Chart("Chart4", {
        type: "line",
        data: {
            labels: xValues.slice(xValues.length - 10),
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgb(255,33,79,0.2)",
                pointBackgroundColor: "rgb(255,33,79)",
                data:soilpH.slice(soilpH.length - 10)
            }]
        },
        options: {
            legend: { display: false },
            scales: {
                yAxes: [{ ticks: { min: 0, max: 14 } }],
            },
            animation: {
                duration: 0
            },
            elements: {
                point :{
                    radius: 5,
                }
                
            }
        }
        
    });
    new Chart("Chart5", {
        type: "line",
        data: {
            labels: xValues.slice(xValues.length - 10),
            datasets: [{
                fill: false,
                lineTension: 0,
                backgroundColor: "rgba(0,0,255,1.0)",
                borderColor: "rgb(255,33,79,0.2)",
                pointBackgroundColor: "rgb(255,33,79)",
                data:uV.slice(uV.length - 10)
            }]
        },
        options: {
            legend: { display: false },
            scales: {
                yAxes: [{ ticks: { min: 0, max: 1000 } }],
            },
            animation: {
                duration: 0
            },
            elements: {
                point :{
                    radius: 5,
                }
                
            }
        }
        
    });
    
}