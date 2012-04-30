<?php get_header(); ?>

<div class="grid_24 content">
	<?php if (have_posts()) : ?>
		<?php while (have_posts()) : the_post(); ?>
			
			<div <?php post_class() ?>>
				

				<?php if ( has_post_thumbnail() ) : ?>
					<div class="post-thumb">
						<a href="<?php the_permalink() ?>"><?php the_post_thumbnail(); ?> </a>
					</div>
  				<?php endif; ?>	
  				
  				<h2 class="post-title"><a href="<?php the_permalink() ?>"><?php the_title(); ?></a></h2>
  				<h2 class="post-date">Posted: <?php the_time('j F Y') ?></h2>
  				
  				<div class="post-content">
  					<?php the_content(''); ?>
  				</div>
  				
  				<p class="post-meta">Posted in <?php the_category(', ') ?> &#124; <?php comments_number('No Comments','1 Comment', '% Comments'); ?></p>
  				
  			</div>
  		<?php endwhile; ?>
  		
  		<div class="pagination">
  			<ul>
  				<li class="older"><?php next_post_link('Older') ?></li>
  				<li class="newer"><?php previous_post_link('Newer') ?></li>
  			</ul>
  		</div>
  		
  		
  	<?php else : ?>
  		<h2>Nothing Found</h2>
  		<p>Sorry, but you are looking for something that isn't here.</p>
  		<p><a href="<?php echo get_option('home'); ?>"</a></p>
  		
	<?php endif; ?>		
</div>
  			
<?php get_footer(); ?>  			
  			
		</div><!-- end .container_24 -->
	</body>
</html>