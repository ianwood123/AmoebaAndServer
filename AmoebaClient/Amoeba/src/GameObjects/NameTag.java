/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameObjects;

import javafx.scene.Node;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 *
 * @author Timothy
 */
public class NameTag extends GameObject {
    public Text model;

    public NameTag(Long id) {
        super(id);
    }

    @Override
    public Node getModel() {
        return model;
    }

    @Override
    public void updateModel(Double x, Double y, Double width, Color c) {
        model = new Text(x, y, model.getText());
        model.setFill(c);
        model.setFont(Font.font("Tahoma", 20));
    }
    
}
