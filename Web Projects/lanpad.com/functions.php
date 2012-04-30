<?php

	if ( function_exists( 'add_theme_support' ) ) { 
		add_theme_support( 'post-thumbnails' );
		set_post_thumbnail_size( 150, 150, true ); // default Post Thumbnail dimensions (cropped)

		// additional image sizes
		// delete the next line if you do not need additional image sizes
		add_image_size( 'category-thumb', 300, 9999 ); //300 pixels wide (and unlimited height)
	}
?>