<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
		+ path + "/";
%>
<!DOCTYPE>
<html>
	<head>
		<base href="<%=basePath%>">
		<meta http-equiv="Content-Type" content="text/html; UTF-8">
		<title>管理平台</title>
		<link rel="stylesheet" type="text/css" href="<%=path %>/css/default.css">
		<link rel="stylesheet" type="text/css" href="<%=path %>/js/jquery-easyui-1.5/themes/default/easyui.css">
		<link rel="stylesheet" type="text/css" href="<%=path %>/js/jquery-easyui-1.5/themes/icon.css">
		<script type="text/javascript" src="<%=path %>/js/jquery-easyui-1.5/jquery.min.js"></script>
		<script type="text/javascript" src="<%=path %>/js/jquery-easyui-1.5/jquery.easyui.min.js"></script>
		<script type="text/javascript" src="<%=path %>/js/jquery-easyui-1.5/easyui-lang-zh_CN.js"></script>
		<script type="text/javascript">
			var rootPath = '<%=basePath %>';
		</script>
		<script type="text/javascript" src="js/login.js"></script>
	</head>
	<body>
		<p>Hello</p>
	</body>
</html>