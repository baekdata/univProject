<?xml version="1.0" encoding="UTF-8" ?>
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title> Login</title>
<link href="resources/adminRsrc/css/bootstrap.min.css" rel="stylesheet">
<!-- Custom Fonts -->
<link href="resources/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css"></link>
<link href="http://fonts.googleapis.com/css?family=Source+Sans+Pro:300,400,700,300italic,400italic,700italic" rel="stylesheet" type="text/css"></link>


<div id = "loginForm" class="col-md-3" style="float:center">	
	<h1 class="text-center">Login</h1>
	<input name="id" type="text" class="form-control input-lg" placeholder="Username">
		<br></br>
	<input name="pw" type="password" class="form-control input-lg" placeholder="Password">
		<br></br>
	<button id="login"class="btn btn-primary btn-lg btn-block">Sign In</button>
		<br></br>
	<a href="/cse">
		<button class="btn" data-dismiss="modal" aria-hidden="true">Cancel</button>
	</a>
</div>	
	
	<!-- script references -->
	<script src="//ajax.googleapis.com/ajax/libs/jquery/2.0.2/jquery.min.js"></script>
	<script src="resources/adminRsrc/js/bootstrap.min.js"></script>	
	

<script type="text/javascript">

$("#login").click(function() {
	username = $("input[name='id']").val(); 
	password = $("input[name='pw']").val();
	adminUrl = "/cse/login"
	console.log(username);
	console.log(password);

	$.post( adminUrl,
		{username: username, password: password}).done(function(html) {
		console.log("logging in!");
		$("#loginForm").html(html);
	});;
});
</script>