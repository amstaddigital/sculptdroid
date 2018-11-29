package com.ad.sculptdroid.Files;

import com.badlogic.gdx.Gdx;

public class ImportExportObj implements ImportExport {

    @Override
    public void importModel() {
        Gdx.app.log("Imp/Exp","Importing OBJ");
    }

    @Override
    public void exportModel() {
        Gdx.app.log("Imp/Exp","Exporting OBJ");
    }

}
