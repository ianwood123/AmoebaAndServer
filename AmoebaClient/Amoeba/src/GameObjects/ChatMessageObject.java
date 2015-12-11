/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GameObjects;

import GameModels.ChatMessageModel;
import javafx.scene.Node;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public class ChatMessageObject extends GameObject {

    final public String message;
    final Long userID;
    final public String username;
    ChatMessageModel model;

    public ChatMessageObject(String m, Long id, String username) {
        super(new Long(-100));
        this.message = m;
        this.userID = id;
        this.username = username;
        model = new ChatMessageModel(m, username);
    }

    @Override
    public Node getModel() {
        return this.model;
    }

    @Override
    public void updateModel(Double x, Double y, Double width, Color c) {
        this.model.setStyle("color:"+c.toString()+";");
    }
    @Override
    public boolean tooDirty(){
         
        return System.currentTimeMillis() > dirt + 100000;
    }
}
