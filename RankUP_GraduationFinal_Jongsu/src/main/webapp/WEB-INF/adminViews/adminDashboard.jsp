<?xml version="1.0" encoding="UTF-8" ?>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html>
<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>ADMIN PAGE</title>

    <!-- Bootstrap Core CSS -->
    <link href="resources/css/bootstrap.min.css" rel="stylesheet"></link>
    <!-- Custom CSS -->
    <link href="resources/css/stylish-portfolio.css" rel="stylesheet"></link>
    <!-- Custom Fonts -->
    <link href="resources/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css"></link>
    <link href="http://fonts.googleapis.com/css?family=Source+Sans+Pro:300,400,700,300italic,400italic,700italic" rel="stylesheet" type="text/css"></link>


    <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
    <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>

</head>

<body>

    <!-- Navigation -->
    <a id="menu-toggle" href="#" class="btn btn-dark btn-lg toggle"><i class="fa fa-bars"></i></a>
    <nav id="sidebar-wrapper">
        <ul class="sidebar-nav">
            <a id="menuClose" href="#" class="btn btn-light btn-lg pull-right toggle">
            	<i class="fa fa-times"></i>
            </a>
            <li class="sidebar-brand">
                <a href="#top"><span class="glyphicon glyphicon-thumbs-up" aria-hidden="true"></span> RankUP Admin</a>
            </li>
            <li>
                <a id ="seoul" href="#portfolio">SEOUL</a>
            </li>
            <li>
                <a id ="gyeonggi" href="#portfolio">GYEONGGI</a>
            </li>
            <li>
                <a id ="jeju" href="#portfolio">JEJU</a> 
            </li>
            <li>
             	<a id ="busan" href="#portfolio">BUSAN</a>
            </li>
            <li>
               <a id ="gangwon" href="#portfolio">GANGWON DO</a> 
            </li>
            <li>
               <a id ="gyeongsang" href="#portfolio">GYEONGNGSANG DO</a>
            </li>
            <li>
               <a id ="choongchung" href="#portfolio">CHOONGCHUNG DO</a>
            </li>
            <li>
               <a id ="jeonra" href="#portfolio">JEONRA DO</a>
            </li>
        </ul>
    </nav>

    <!-- Header -->
    <header id="top" class="header">
    <div class="text-vertical-center">
        <h1>WECLOME <span class="glyphicon glyphicon-thumbs-up" aria-hidden="true"></span>	RankUP ADMIN!</h1>
        <!-- DGUCSE GRUDATION PROJECT(KELLY) -->
    </div>
    </header>
    <!-- Portfolio -->
    <section id="portfolio" class="portfolio">
       	<div id="contents"></div>
	</section>
    
    <!-- jQuery -->
    <script src="resources/js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="resources/js/bootstrap.min.js"></script>

    <!-- Custom Theme JavaScript -->
    <script type="text/javascript">
	    // Closes the sidebar menu
	    $("#menuClose").click(function(e) {
	        e.preventDefault();
	        $("#sidebar-wrapper").toggleClass("active");
	    });
	
	    // Opens the sidebar menu
	    $("#menu-toggle").click(function(e) {
	        e.preventDefault();
	        $("#sidebar-wrapper").toggleClass("active");
	    });
	
	    // Scrolls to the selected menu item on the page
	    $(function() {
	        $('a[href*=#]:not([href=#])').click(function() {
	            if (location.pathname.replace('/^\//', '') == this.pathname.replace('/^\//', '') || location.hostname == this.hostname) {
	
	                var target = $(this.hash);
	                target = target.length ? target : $('[name=' + this.hash.slice(1) + ']');
	                if (target.length) {
	                    $('html,body').animate({
	                        scrollTop: target.offset().top
	                    }, 1000);
	                    return false;
	                }
	            }
	        });
		})
		
		$(document).ready(function() {
			
			readyUrl = "/cse/ready";
			
			$.post(readyUrl).done(function(html) {
				$("#contents").html(html);
				console.log("mainDashboard is loaded");
			});
			
			$("#seoul").click(function() {
				$('#contents').load('/cse/seoul');
				console.log("seoul is loaded")
			});
			
			$("#busan").click(function() {
				$('#contents').load('/cse/busan');
				console.log("seoul is loaded")
			});
			$("#gyeonggi").click(function() {
				$('#contents').load('/cse/gyeonggi');
				console.log("gyeonggi is loaded")
			});
			$("#jeju").click(function() {
				$('#contents').load('/cse/jeju');
				console.log("jeju is loaded")
			});
			
			$("#gangwon").click(function() {
				$('#contents').load('/cse/gangwon');
				console.log("gangwon is loaded")
			});
			$("#gyeongsang").click(function() {
				$('#contents').load('/cse/gyeongsang');
				console.log("gyeongsang is loaded")
			});
			$("#jeonra").click(function() {
				$('#contents').load('/cse/jeonra');
				console.log("jeonra is loaded")
			});
			
			$("#choongchung").click(function() {
				$('#contents').load('/cse/choongchung');
				console.log("choongchung is loaded")
			});
		});
    </script>

</body>

</html>
