/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameModels;

import javafx.scene.paint.Color;
import javafx.scene.text.Text;

/**
 *
 * @author woodi
 */
public class ChatMessageModel extends Text{

    public ChatMessageModel(String m, String username) {
        super();
        this.setText(username+"> "+m);
        this.setSmooth(true);
        this.setFill(Color.YELLOW);
        this.setTranslateX(0);
        this.setTranslateY(100);
    }

}

