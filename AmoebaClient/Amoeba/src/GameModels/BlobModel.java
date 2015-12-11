/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameModels;

import GameObjects.NameTag;
import javafx.collections.ObservableList;
import javafx.scene.Node;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;

/**
 *
 * @author woodi
 */
public class BlobModel extends Pane {
    public String username;
    public BlobModel(Double x, Double y, Double width, Color color, String username){
        super();
        this.username = username;
        this.getChildren().add(new Circle(x,y,width/2,color));
            Text nt = new Text(x, y, username);
            nt.setFill(color);
            nt.setFont(Font.font("Tahoma", 20));
            nt.setY(y-(width/2));
            nt.setTextAlignment(TextAlignment.CENTER);
            nt.setLayoutX(-username.length()*5);
        this.getChildren().add(nt);
        
//        this.setMinWidth(width);
//        this.setTranslateX(x-width/2);
//        this.setTranslateY(y-width/2);
    }
    
}
