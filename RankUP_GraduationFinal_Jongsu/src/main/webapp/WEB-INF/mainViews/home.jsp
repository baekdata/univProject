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

    <title>RankUP</title>

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
                <a href="#top"><span class="glyphicon glyphicon-thumbs-up" aria-hidden="true"></span> RankUP</a>
            </li>
            <li>
                <a href="#top"><span class="glyphicon glyphicon-home" aria-hidden="true"></span>&nbsp;&nbsp;Home</a>
            </li>
            <li>
                <a href="#about"><span class="glyphicon glyphicon-search" aria-hidden="true"></span>&nbsp;&nbsp;Services</a>
            </li>
            <li>
                <a href="#contact"><span class="glyphicon glyphicon-earphone" aria-hidden="true"></span>&nbsp;&nbsp;Contact</a>
            </li>
            <li>
                <a href="adminLogin" ><span class="glyphicon glyphicon-user" aria-hidden="true"></span>&nbsp;&nbsp;Admin</a>
            </li>
        </ul>
    </nav>

    <!-- Header -->
    <header id="top" class="header">
        <div class="text-vertical-center">
            <h1><span class="glyphicon glyphicon-thumbs-up" aria-hidden="true"></span>	RankUP</h1>
            <h3>We Provide Rank Lists of Restaurants by utilizing blog posts data <span class="glyphicon glyphicon-cutlery" aria-hidden="true"></span></h3>
            <!-- DGUCSE GRUDATION PROJECT(KELLY) -->
            <br>
            <a href="#about" class="btn btn-dark btn-lg">Find Out More</a>
        </div>
    </header>
    <br></br>
    <!-- Services -->
    <!-- The circle icons use Font Awesome's stacked icon classes. For more information, visit http://fontawesome.io/examples/ -->
    <section id="about" class="portflio">
        <div class="container">
            <div class="row text-center">
                <div class="col-lg-10 col-lg-offset-1">
                    <div class="row">
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="/seoul" class="btn btn-light"><strong>SEOUL</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>GYEONG GI</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>JEJU</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>BUSAN</strong></a>
                            </div>
                        </div>
                    </div>
                    <!-- /.row (nested) -->
                    <div class="row">
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>GANGWON DO</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>GYUNGSANG DO</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>CHOONGCHUNG DO</strong></a>
                            </div>
                        </div>
                        <div class="col-md-3 col-sm-6">
                            <div class="service-item">
	                            <span class="fa-stack fa-4x">
	                                <i class="glyphicon glyphicon-cutlery"></i>
	                            </span>
	                            <HR></HR>
                                <a href="#" class="btn btn-light"><strong>JEONRA DO</strong></a>
                            </div>
                        </div>
                    </div>
                    <!-- /.row (nested) -->
                </div>
                <!-- /.col-lg-10 -->
            </div>
            <!-- /.row -->
        </div>
        <!-- /.container -->
    </section>
    <br></br>
	<!-- Callout -->
    <aside class="callout">
        <div class="text-vertical-center">
            <h1>SELECT AREA NAME ABOVE</h1>
        </div>
    </aside>
	<section id="contact" class="about">
    <!-- Footer -->
    <footer>
        <div class="container">
            <div class="row">
                <div class="col-lg-10 col-lg-offset-1 text-center">
                    <h4><strong><span class="glyphicon glyphicon-thumbs-up" aria-hidden="true"></span>	RankUP</strong></h4>
                    <h5>Juhee Lee &amp; Donguk Kim &amp; Jongsu Baek &amp; Joowon Jung</h5>
                    
                    <p>Dongguk University (Seoul Campus) - CSE Graduation Final Project</p>
                    <ul class="list-unstyled">
                        <li><i class="fa fa-phone fa-fw"></i> 010 - 9157 - 7514</li>
                        <li><i class="fa fa-envelope-o fa-fw"></i>  <a href="mailto:swdeveloperkelly@gmail.com">swdeveloperkelly@gmail.com</a>
                        </li>
                    </ul>
                    <br>
                    <ul class="list-inline">
                        <li>
                            <a href="#"><i class="fa fa-facebook fa-fw fa-3x"></i></a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-twitter fa-fw fa-3x"></i></a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-dribbble fa-fw fa-3x"></i></a>
                        </li>
                    </ul>
                    <hr class="small">
                    <p class="text-muted">Copyright &copy; Dongguk CSE Kelly 2015</p>
                </div>
            </div>
        </div>
    </footer>
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
    
	
    
    </script>

</body>

</html>
