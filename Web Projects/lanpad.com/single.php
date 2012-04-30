<?php get_header(); ?>

<div class="grid_24 content">
	<?php if (have_posts()): ?>
	<?php while (have_posts()) : the_post(); ?>
		
			<?php if ( has_post_thumbnail() ) : ?>
					<div class="post-thumb">
						<a href="<?php the_permalink() ?>"><?php the_post_thumbnail(); ?> </a>
					</div>
  			<?php endif; ?>	
		
			<h2 class="post-title"><?php the_title(); ?></h2>
				
			<div class="post-content">
  				<?php the_content(''); ?>
  			</div>
		
		<?php comments_template(); ?>
		
		<?php endwhile; ?>
		<?php endif; ?>
<?php get_footer(); ?>
