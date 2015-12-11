/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameObjects;

import GameModels.PelletModel;
import javafx.scene.Node;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public class Pellet extends GameObject {

    PelletModel model;
    Double x, y;

    public Pellet(Double x, Double y, Color color, Long id) {
        super(id);
        this.x = x;
        this.y = y;
        model = new PelletModel(x, y, color);
    }

    @Override
    public Node getModel() {
        return this.model;
    }

    @Override
    public void updateModel(Double x, Double y, Double width, Color c) {
        x += (this.x - x)/1000;
        y += (this.y - y)/1000;
        model = new PelletModel(x, y, c);
//        model.relocate(x, y);
    }
}
