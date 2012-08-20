<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8" />
		<title><?php bloginfo('name'); ?> - <?php bloginfo('description'); ?></title>
		<link rel="stylesheet" href="<?php bloginfo('template_directory'); ?>/reset.css" />
		<link rel="stylesheet" href="<?php bloginfo('template_directory'); ?>/960_24_col.css" />
		<link rel="stylesheet" href="<?php bloginfo('template_directory'); ?>/style.css" />
	</head>
	
	<body>

		<div class="container_24">
  			<div class="grid_24" id="header">
  				<a href="<?php echo get_option('home'); ?>">
  					<img src="<?php bloginfo('template_directory'); ?>/images/header.png" alt="header">
  				</a>
  			</div>
  			
  			<div class="grid_24 navigation-bar">
  				<div class="grid_4 alpha border-right"><a href="<?php echo get_option('home')?>">Home</a></div>
  			  	<div class="grid_4 border-right"><a href="http://lanpad.com/project/">Projects</a></div>
  				<div class="grid_4 border-right"><a href="#">Twitter</a></div>
  				<div class="grid_4 border-right"><a href="#">Links</a></div>
  				<div class="grid_4 border-right"><a href="#">Downloads</a></div>
  				<div class="grid_4 omega"><a href="#">Link 8</a></div>
  			</div>