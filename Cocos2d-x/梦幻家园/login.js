$(document).ready(function() {
    //图片验证码控制
    $('.change-captcha').on('click', function() {
        var url =  $(this).attr('src');
        var index = url.indexOf('?');
        if(index !== -1) {
            $(this).attr('src', url.substring(0, index)+'?'+Math.random());
        } else {
            $(this).attr('src', url+'?'+Math.random());
        }
    }).css('cursor', 'pointer').attr('title', '看不清？点击更换');

    //短信验证码控制
    var s = 60;
    $('.get-sms-code').on('click', function() {
        if(s>0 && s<60) {
            return false;
        }
        var url = $(this).attr('href');
        var oldval = $(this).text();
        $(this).text('获取中..');
        var self = this;
        $.post(url, {
            mobile: $("#mobile").val(),
            captcha: $("#captcha").val()
        }, function(data) {
            if(data.code ===0) {
                $('.change-captcha').click().hide();
                $(self).text(s+'秒后重新获取');
                var timer = window.setInterval(function() {
                    s--;
                    $(self).text(s+'秒后重新获取');
                    if(s < 1) {
                        s=60;
                        window.clearInterval(timer);
                        $(self).text(oldval);
                        $('.change-captcha').show();
                    }
                }, 1000);
            } else {
                if(8 == data.code) {
                    var obj = $("#mobile");
                } else if(7 == data.code) {
                    var obj = $("#captcha");
                } else {
                    var obj = $("#smscode");
                }
                obj.attr('validform_valid', false);
                var oval = obj.val();
                $('#doSubmit').attr('disabled', 'disabled');
                var oplaceholder = obj.attr('placeholder');
                obj.val('').attr('placeholder', data.msg);
                obj.parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "0px" }, 100, 'swing', function() {
                        window.setTimeout(function() {
                            obj.val('').attr('placeholder', oplaceholder);
                            $('#doSubmit').removeAttr('disabled');
                        }, 500);

                    });
            }
            $(self).text(oldval);
        });
        return false;
    });
    $("#laya_form").Validform({
        tipSweep:false,
        datatype: {
            "u4-16": /^[a-zA-Z][a-zA-Z0-9-_]{3,16}$/
        },
        tiptype: function(msg, o, cssctl) {
            if(o.type > 2) {
                var oval = o.obj.val();
                $('#doSubmit').attr('disabled', 'disabled');
                var oplaceholder = o.obj.attr('placeholder');
                o.obj.val('').attr('placeholder', msg);
                o.obj.parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "0px" }, 100, 'swing', function() {
                        window.setTimeout(function() {
                            o.obj.val(oval).attr('placeholder', oplaceholder);
                            $('#doSubmit').removeAttr('disabled');
                        }, 500);

                    });
            }
        },
        beforeSubmit: function() {
            var doSubmitVal = $('#doSubmit').val();
            return LAYA_PLATFORM.formSend($("#laya_form"), function () {
                $('#doSubmit').val('请求中...').attr('disabled', 'disabled');
            }, function (data) {
                $('#doSubmit').val(doSubmitVal).removeAttr('disabled');
                if(data.url) {
                    top.location.href = data.url
                } else {
                    top.location.reload();
                }
            }, function (data) {
                $('#doSubmit').val(data.msg).parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "0px" }, 100, 'swing', function() {
                        window.setTimeout(function() {
                            $('#doSubmit').val(doSubmitVal).removeAttr('disabled');
                            $('.change-captcha').click();
                        }, 600);
                    });

            });
        },
        ajaxurl: {
            success:function(data,obj){
                if(data.code === 0) {
                    obj[0].validform_valid = "true";
                } else {
                    obj[0].validform_valid = "false";
                    var oval = obj.val();
                    $('#doSubmit').attr('disabled', 'disabled');
                    var oplaceholder = obj.attr('placeholder');
                    obj.val('').attr('placeholder', data.msg);
                    obj.parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                        .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                        .animate({ left: "0px" }, 100, 'swing', function() {
                            window.setTimeout(function() {
                                obj.val('').attr('placeholder', oplaceholder);
                                $('#doSubmit').removeAttr('disabled');
                            }, 500);

                        });
                }
            }
        }
    });
});