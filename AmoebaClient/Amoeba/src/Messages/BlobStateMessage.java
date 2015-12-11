/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Messages;

import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */

public class BlobStateMessage extends Message{
    
    public final Double x;
    public final Double y;
    public final Double size;
    public final String color;
    public final String username;
    public final Long id;
    
    public BlobStateMessage(Double x, Double y, Double size, String color, String username, Long id){
        this.x = x;
        this.y = y;
        this.size = size;
        this.color = color; 
        this.username = username;
        this.id = id;
    }
}
