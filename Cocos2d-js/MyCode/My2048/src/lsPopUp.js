  function ls_show(content,backFun){

  var html =  '<div id="lsMess" style="width: 100%;height: 100%;position: absolute;z-index: 100;top: 0;left: 0;text-align: center;background-color: rgba(0, 0, 0, 0.67);"><div style="'+

   'display: block;'+
    'margin-top: 50%;'+
    'position: absolute;'+
    'top: 50%;'+
    'left: 50%;'+
    'width: 60%;'+
    'height: 26%;'+
    'margin-top: -26%;'+
    'margin-left: -30%;'+
    'background-color: #F6F6F6;'+
    'border: 3px solid #5CB0DF;'+
    'float: left;'+
'"><span style="'+
    'width: 100%;'+
    'height: 18%;'+
    'float: left;'+
    'text-align: left;'+
    'color: #fff;'+
    'line-height: 30px;'+
    'font-size: 16 px;'+
    'background-color: #5CB0DF;'+
    /* position: relative;'+ */
'">提示</span><span style="'+
    'width: 100%;'+
    'height: 60%;'+
    'float: left;'+
    'text-align: center;'+
    'color: #000;'+
    'line-height: 30px;'+
    'font-size: 14px;'+
      'font-weight: bold;'+
      'overflow-y: auto;'+
    /* position: absolute;'+ */
'">'+content+'</span><input id="ls_BtnId"  type="button" value="确定" style="'+
    'width: 30%;'+
    'height: 15%;'+
    'margin-top: 1.5%;'+
    'background-color: #5CB0DF;'+
    'color: #fff;'+
    'border-color: #6EC0EE;'+
'"></div></div>';
      $('#lsMess').remove();
  $('body').append(html);
      $('#ls_BtnId').one('click',function(){
          $('#lsMess').remove();
          if(backFun){
              backFun();
          }
      })

  }
