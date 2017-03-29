/**
 * Created by 陈鸿 on 2016/4/7.
 */
$(function () {
    $(".open-header a").click(function () {
        var num = $(this).index();
        $(this).addClass('checked').siblings().removeClass('checked');
        $(".item").eq(num).show().siblings('.item').hide();
    })

    $(".have").click(function () {
        $(".open-header a").eq(0).addClass('checked').siblings().removeClass('checked');
        $(".item").eq(0).show().siblings('.item').hide();
    })


    $("#laya_reg_form").Validform({
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
            var doSubmitVal = $('#doRegSubmit').val();
            return LAYA_PLATFORM.formSend($("#laya_reg_form"), function () {
                $('#doRegSubmit').val('请求中...').attr('disabled', 'disabled');
            }, function (data) {
                console.log(data)
                $('#doRegSubmit').val(doSubmitVal).removeAttr('disabled');
                if(data.url) {
                    top.location.href = data.url
                } else {
                    top.location.reload();
                }
            }, function (data) {
                $('#doRegSubmit').val(data.msg).parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                    .animate({ left: "0px" }, 100, 'swing', function() {
                        window.setTimeout(function() {
                            $('#doRegSubmit').val(doSubmitVal).removeAttr('disabled');
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
                    $('#doRegSubmit').attr('disabled', 'disabled');
                    var oplaceholder = obj.attr('placeholder');
                    obj.val('').attr('placeholder', data.msg);
                    obj.parent().animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                        .animate({ left: "-5px" }, 100).animate({ left: "5px" }, 100)
                        .animate({ left: "0px" }, 100, 'swing', function() {
                            window.setTimeout(function() {
                                obj.val('').attr('placeholder', oplaceholder);
                                $('#doRegSubmit').removeAttr('disabled');
                            }, 500);

                        });
                }
            }
        }
    });
})


