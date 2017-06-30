/**
 * Created by JackerCao on 2016/11/26.
 */


(
    function () {

        var div=document.getElementById("share_Div");
        var hg=$(window).height();
        div.style.height=hg+"px";

        if(document.documentElement.clientWidth>720){
            document.documentElement.style.fontSize = "100px";
        }else{
            document.documentElement.style.fontSize = document.documentElement.clientWidth/7.2+ "px";
        }
    }
)();



//从后端得到次数;
    function getNumber() {

    var uId= GetQueryString('userId');
    var nickName=decodeURI(GetQueryString('nickname'));
    if(nickName=="null"){
        nickName="测试";
    }
    $.ajax({

        //英语拼写第一次请求;
        url: "http://211.157.179.218:8780/hxs_personaltutor_wechat/gameController/getUserWGameMessage",
        dataType: "json",
        async: true,
        data: {
            "userId":uId,
            "userNick":nickName
        },
        type: "POST",
        success: function(req) {
            // 游戏剩余次数;
            var num=req["result"]["overplusTimes"];
            RCCommon.UpdateLives(num);

        },
        error: function() {
            alert("ee");
        }
    });
}


function addDataLi(num,name,score) {
    var ul=document.getElementsByClassName("data_Ul")[0];
    // ul.innerHTML="";

    var li=document.createElement("li");

    var divL=document.createElement("div");
    divL.className='dataL_Div clear';
    var spanL=document.createElement("span");
    spanL.innerHTML=num;
    divL.appendChild(spanL);

    var divC=document.createElement("div");
    divC.className='dataC_Div clear';
    var spanC=document.createElement("span");
    spanC.innerHTML=name;
    divC.appendChild(spanC);

    var divR=document.createElement("div");
    divR.className='dataR_Div clear';
    var spanR=document.createElement("span");
    spanR.innerHTML=score;
    divR.appendChild(spanR);

    li.appendChild(divL);
    li.appendChild(divC);
    li.appendChild(divR);

    ul.appendChild(li);
}


//剩余次数;
var residueNum=0;


//从游戏得到分数;
//像服务器发送得分，请求得到得分、排名、排行榜、可以玩次数数据;
function showDiv(time){
    var uId= GetQueryString('userId');


    //英语拼写第二次交互;
    $.ajax({
        url: "http://211.157.179.218:8780/hxs_personaltutor_wechat/gameController/updateWGameList",
        dataType: "json",
        async: true,
        data: { "userId":uId,
                "gameTime":time,
        },
        type: "POST",
        success: function(req) {

            var div=document.getElementById('myDiv');
            div.style.display='block';

            //排行榜;
            var num=req["result"]["rankList"];
            createLi(num);

            //排名;
            var  rank =  req["result"]["user"]["rank"];
            $(".scoreBG_span")[0].innerHTML=rank;

            //得分;
            var  _score =  req["result"]["user"]["game_time"];
            $(".scoreBG_P")[0].innerHTML=_score+"秒";

            //剩余次数;
            var  shengyuNum =  req["result"]["user"]["overplus_times"];
            $(".shengyuNum")[0].innerHTML=shengyuNum;
            RCCommon.Lives=shengyuNum;
            
        },
        error: function() {
            setTimeout(function () {
                var div=document.getElementById('noNet');
                div.style.display='block';
            },1500);

        }
    });
}


function createLi (obj){

    // var ul=document.getElementsByClassName("data_Ul")[0];
    // ul.innerHTML="";

    $('.data_Ul').html("");

    var num=obj.length;
    for(var i=0;i<num;i++){
        var n=obj[i]["rank"];
        var userNick=obj[i]["user_nick"];
        var score=obj[i]["game_time"];
        addDataLi(n,userNick,score);
    }
}


function GetQueryString(name)
{
    var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
    var r = window.location.search.substr(1).match(reg);
    if(r!=null) return  r[2]; return null;
}

//再来一次btn回调;
function  restartGame(){
    RCCommon.RestartGame();
    var div=document.getElementById('myDiv');
    div.style.display='none';
}

function noNetworkBack(){
    var netDiv=document.getElementById('noNet');
    netDiv.style.display='none';
    showDiv();
}

