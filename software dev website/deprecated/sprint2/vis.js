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
		ctx.fillStyle = "#FFFF";
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