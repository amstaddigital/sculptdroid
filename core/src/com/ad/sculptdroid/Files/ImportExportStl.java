package com.ad.sculptdroid.Files;

import com.badlogic.gdx.Gdx;

public class ImportExportStl implements ImportExport {
    @Override
    public void importModel() {
        Gdx.app.log("Imp/Exp","Importing STL");
    }

    @Override
    public void exportModel() {
        Gdx.app.log("Imp/Exp","Exporting STL");
    }
}
