<?php get_header(); ?>

<div class="grid_24 content">
	<?php if (have_posts()) ?>
	<?php while (have_posts()) : the_post(); ?>
		
		<div class="post">
			<h2 class="title"><?php the_title(); ?></h2>
			
			<?php if ( has_post_thumbnail() : ?>)
				<div class="post-thumb">
					<a href="<?php the_permalink() ?>"><?php the_post_thumbnail(); ?></a>
				</div>
				<?php endif; ?>
				
				<?php the_content(); ?>
		</div>
		
		<?php endwhile; ?>
		<?php endif; ?>
	<?php get_footer(); ?>
