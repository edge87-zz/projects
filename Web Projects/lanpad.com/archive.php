<?php get_header(); ?>

<div class="grid_24 content">
	<?php if (have_posts())?>
	
	<?php if (is_category()) :{ ?>
			<h2 class="cat-title-archive"><?php single_cat_title(); ?></h2>
		<?php } elseif (is_month()) : { ?>
			<h2 class="cat-title-archive"><?php the_time('F, Y'); ?></h2>
		<?php } ?>
	<?php endif; ?>
	
	<?php while (have_posts()) : the_post(); ?>
		<h2 class="post-title-archive"><a href="<?php the_permalink() ?>"><?php the_title(); ?></a></h2>		
		<h2 class="post-date-archive">Posted: <?php the_time('j F Y') ?></h2>		
	<?php endwhile; ?>

<?php get_footer(); ?>
