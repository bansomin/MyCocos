var TestWebGLSupport=(function(){
	function TestWebGLSupport(){
		this._VSHADER_SOURCE='attribute vec4 a_Position;\n'+'void main() {\n'+'  gl_Position = a_Position;\n'+'}\n';
		this._FSHADER_SOURCE='void main() {\n'+'  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n'+'}\n';
		this._canvasWidth=256;
		this._canvasHeight=256;
	}
	var __proto=TestWebGLSupport.prototype;
	__proto.checkWebGlSupport=function(){
		var canvas=window.document.createElement('canvas');
		canvas.width=this._canvasWidth;
		canvas.height=this._canvasHeight;
		var names=["webgl","experimental-webgl","webkit-3d","moz-webgl"];
		var gl=null;
		for (var i=0;i < names.length;i++){
			try {
				var opt_attribs=null;
				gl=canvas.getContext(names[i],{stencil:true,alpha:false,antialias:true,premultipliedAlpha:false});
			}catch (e){}
			if (gl){
				break ;
			}
		}
		if (!gl){
			console.log("创建WebGL失败！");
			return false;
		}
		if (!this.initShaders(gl,this._VSHADER_SOURCE,this._FSHADER_SOURCE)){
			console.log("创建Shader失败！");
			return false;
		};
		var n=this.initVertexBuffers(gl);
		if (n < 0){
			console.log("创建顶点失败！");
			return false;
		}
		gl.clearColor(0,0,0,1);
		gl.clear(gl.COLOR_BUFFER_BIT);
		gl.drawArrays(gl.TRIANGLE_STRIP,0,n);
		var pixels=new Uint8Array(4);
		gl.readPixels(this._canvasWidth / 2,this._canvasHeight / 2,1,1,gl.RGBA,gl.UNSIGNED_BYTE,pixels);
		if (pixels[0]===255){
			console.log(pixels);
			console.log("支持WebGL");
			return true;
		}
		return false;
	}

	__proto.initVertexBuffers=function(gl){
		var vertices=new Float32Array([-0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,-0.5]);
		var n=4;
		var vertexBuffer=gl.createBuffer();
		if (!vertexBuffer){
			console.log("创建VertexBuffer失败！");
			return-1;
		}
		gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer);
		gl.bufferData(gl.ARRAY_BUFFER,vertices,gl.STATIC_DRAW);
		var a_Position=gl.getAttribLocation(gl.program,'a_Position');
		if (a_Position < 0){
			console.log("获取Shader中顶点位置失败！");
			return-1;
		}
		gl.vertexAttribPointer(a_Position,2,gl.FLOAT,false,0,0);
		gl.enableVertexAttribArray(a_Position);
		return n;
	}

	__proto.initShaders=function(gl,vshader,fshader){
		var program=this.createProgram(gl,vshader,fshader);
		if (!program){
			console.log("创建WebGLProgram失败！");
			return false;
		}
		gl.useProgram(program);
		gl.program=program;
		return true;
	}

	__proto.createProgram=function(gl,vshader,fshader){
		var vertexShader=this.loadShader(gl,gl.VERTEX_SHADER,vshader);
		var fragmentShader=this.loadShader(gl,gl.FRAGMENT_SHADER,fshader);
		if (!vertexShader || !fragmentShader){
			return null;
		};
		var program=gl.createProgram();
		if (!program){
			return null;
		}
		gl.attachShader(program,vertexShader);
		gl.attachShader(program,fragmentShader);
		gl.linkProgram(program);
		var linked=gl.getProgramParameter(program,gl.LINK_STATUS);
		if (!linked){
			var error=gl.getProgramInfoLog(program);
			console.log('连接WebGlProgram失败 '+error);
			gl.deleteProgram(program);
			gl.deleteShader(fragmentShader);
			gl.deleteShader(vertexShader);
			return null;
		}
		return program;
	}

	__proto.loadShader=function(gl,type,source){
		var shader=gl.createShader(type);
		if (shader==null){
			console.log("无法创建Shader");
			return null;
		}
		gl.shaderSource(shader,source);
		gl.compileShader(shader);
		var compiled=gl.getShaderParameter(shader,gl.COMPILE_STATUS);
		if (!compiled){
			var error=gl.getShaderInfoLog(shader);
			console.log("编译Shader是失败！:"+error);
			gl.deleteShader(shader);
			return null;
		}
		return shader;
	}

	return TestWebGLSupport;
})()