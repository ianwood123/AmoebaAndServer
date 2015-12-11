/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameModels;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

/**
 *
 * @author woodi
 */
public class PelletModel extends Circle{
    
    public PelletModel(Double x, Double y, Color col){
        super(x,y,3,col);
    }
}
