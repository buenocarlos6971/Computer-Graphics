
// THIS WAS FROM THE AVOKE-LOGIN.JS

function openModal() {    
    var myInput = document.getElementById("psw");
    var confirmMyInput = document.getElementById("cpsw");
	var letter = document.getElementById("letter");
	var capital = document.getElementById("capital");
	var number = document.getElementById("number");
	var length = document.getElementById("length");    
    var match = document.getElementById("match");


	// When the user starts to type something inside the password field
	// myInput.onkeyup = function() {
    //    console.log('helllooo')
        
    //     var lowerCaseLetters = /[a-z]/g; 
    //     var upperCaseLetters = /[A-Z]/g; 
    //     var numbers = /[0-9]/g; 
    //     var minLength = 8; 
    

    //     // Validate lowercase letters
    //     if(myInput.value.match(lowerCaseLetters)) {             
    //         letter.classList.remove("invalid"); 
    //         letter.classList.add("valid"); 
    //     } else {
    //         letter.classList.remove("valid"); 
    //         letter.classList.add("invalid"); 
    //     }

    //     // Validate capital letters        
    //     if(myInput.value.match(upperCaseLetters)) { 
    //         capital.classList.remove("invalid"); 
    //         capital.classList.add("valid");
    //     } else {
    //         capital.classList.remove("valid");
    //         capital.classList.add("invalid");
    //     }

    //     // Validate numbers        
    //     if(myInput.value.match(numbers)) { 
    //         number.classList.remove("invalid"); 
    //         number.classList.add("valid"); 
    //     } else {
    //         number.classList.remove("valid"); 
    //         number.classList.add("invalid");
    //     }

    //     // Validate length
    //     if(myInput.value.length >= minLength) {
    //         length.classList.remove("invalid");
    //         length.classList.add("valid");
    //     } else {
    //         length.classList.remove("valid");
    //         length.classList.add("invalid");
    //     }
    // }

    // confirmMyInput.onkeyup = function() {
    //             // Validate password and confirmPassword
    //             var passEqualsConfPass = (false); 
    //             if(passEqualsConfPass) { 
    //                 match.classList.remove("invalid"); 
    //                 match.classList.add("valid"); 
    //             } else {
    //                 match.classList.remove("valid"); 
    //                 match.classList.add("invalid"); 
    //             }        

    //             // Disable or Enable the button based on the elements in classList
    //             enableButton(letter, capital, number, length, match);
    // }
}


function enableButton(letter, capital, number, length, match) {
    if(letter.enabled && capital.enabled && number.enabled && length.enabled && match.enabled) {
        result = false;
    }
    else {
        result = true;
    }   
    var button = document.getElementById('my_submit_button');
    var condition = (result); 
    if(condition) {       
            button.disabled = false;
        }        
    }    


function onClickFunction() {
    alert("Hey! I'm all green! Well done.")
}


// THIS WAS FROM SET_VIS.JS
window.onload = function() { //citing https://developer.mozilla.org/en-US/docs/Web/API/AnalyserNode/frequencyBinCount
	var file = document.getElementById("fileid");
	var audio = document.getElementById("audioid");
	
	file.onchange = function() {
	  var files = this.files;
	  audio.src = URL.createObjectURL(files[0]);
	  audio.load();
	  audio.play();
	  var a_context = new AudioContext();
	  var src = a_context.createMediaElementSource(audio);
	  var analyser = a_context.createAnalyser();
	  var canvas = document.getElementById("canvasid");
	  canvas.width = window.innerWidth;
	  canvas.height = window.innerHeight;
	  var ctx = canvas.getContext("2d");
	  src.connect(analyser);
	  analyser.connect(a_context.destination);
	  analyser.fftSize = 2048;
	  var b_length = analyser.frequencyBinCount;
	  console.log(b_length);
	  var d_arr = new Uint8Array(b_length);
	  var w = canvas.width;
	  var h = canvas.height;
	  var b_w = (w / b_length) * 1.5;
	  var b_h;
	  var x = 0;
	  function renderFrame() { //citiing https://developer.mozilla.org/en-US/docs/Web/API/window/requestAnimationFrame
		requestAnimationFrame(renderFrame);
		x = 0;
		analyser.getByteFrequencyData(d_arr);
		ctx.fillStyle = "#10111E";
		ctx.fillRect(0, 0, w, h);
		for (var i = 0; i < b_length; i++) {
		  b_h = d_arr[i]*2.5;
		  ctx.fillStyle = 'rgb(14, 160, 229)';
		  ctx.fillRect(x, h - b_h, b_w, b_h);
		  x += b_w + 1;
		}
	  }
	  audio.play();
	  renderFrame();
	};
  };


  function signUpFunc(){
      var tempFN = document.getElementById("first_name").value;
      var tempLN = document.getElementById("last_name").value;
      var tempE = document.getElementById("email").value;
      var tempP = document.getElementById("passw").value;
    $(document).ready(function(){
      $.ajax({url:"localhost:3000/login/signup", dataType:"json", method:'post', data: 
      {first_name: tempFN, last_name:tempLN, email: tempE, pass: tempP }}).then(function(data) {})
    })
  };