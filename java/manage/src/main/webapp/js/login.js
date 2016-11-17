//登陆
function login() {
	$("#account").textbox({
		required: 'true',
		missingMessage: '用户名不能为空！'
	});
	$("#passwd").textbox({
		required: 'true',
		missingMessage: '密码不能为空！'
	});
	$.ajax({ 
        type: 'POST',
        dataType: "json",
        data: {account: $("#account").textbox('getValue'),passwd: $("#passwd").textbox('getValue')},
	    url: rootPath+'user/login.do',
	    success:function(data){
	    	
	    	if(data.ret == 1) {
	    		$.messager.alert('警告消息', data.desc, 'warning');
	    	} else if(data.ret == 0) {
	    		location.href = rootPath+"user/index.do";
	    	}
	    },
	     error:function(data){
              return $.messager.alert('警告消息',"用户名或密码不正确!","warning");
     	}
	});
}