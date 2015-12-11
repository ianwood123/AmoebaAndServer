/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameObjects;

import javafx.scene.Node;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public abstract class GameObject {
    
    public abstract Node getModel();
    
    public abstract void updateModel(Double x, Double y, Double width, Color c);
    
    public final Long id;
    
    protected GameObject(Long id){
        this.id = id;
    }
    
    protected Long dirt = System.currentTimeMillis();
    
    public void resetDirt(){
        dirt = System.currentTimeMillis();
    }
    
    public boolean tooDirty(){
         
        return System.currentTimeMillis() > dirt + 250;
    }
}
