/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameObjects;

import GameModels.BlobModel;
import javafx.scene.Node;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public class Blob extends GameObject{
    BlobModel model;
    Double x, y;
    
    public Blob(Double x, Double y, Double width, Color c, Long id, String username){
        super(id);
        this.x = x;
        this.y = y;
        model = new BlobModel(x,y, width, c, username);
        
    }

    @Override
    public Node getModel() {
        return this.model;
    }
    
    @Override
    public void updateModel(Double x, Double y, Double width, Color c){
        x += (this.x - x)/1000;
        y += (this.y - y)/1000;
        model = new BlobModel(x,y, width, c, model.username);
//        model.relocate(x, y);
    }
    
}
