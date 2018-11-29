package com.ad.sculptdroid;


import com.ad.sculptdroid.Utils.Utils;
import com.badlogic.gdx.Application;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;



public class Sculptdroid extends ApplicationAdapter {

	Utils utils = new Utils();

	private BitmapFont font;
	private SpriteBatch batch;
	
	@Override
	public void create () {
		// Initialize
		font = new BitmapFont();
		batch = new SpriteBatch();


		// For development only
		Gdx.app.setLogLevel(Application.LOG_DEBUG);

	}

	@Override
	public void render () {


		// DEBUG ONLY
		if(Gdx.input.isKeyPressed(Input.Keys.SPACE)) {
			Gdx.app.log("Profile", "Profiling method");
		}


		Gdx.gl.glClearColor(0, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

		batch.begin();
		font.draw(batch, "Hello World!", 150, 150);
		batch.end();


	}

	@Override
	public void resize (int width, int height) {
	}

	@Override
	public void pause () {
	}

	@Override
	public void resume () {
	}

	
	@Override
	public void dispose () {

	}

}
