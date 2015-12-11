/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Messages;

/**
 *
 * @author woodi
 */
public class PelletPositionMessage extends Message{
    final public Double x;
    final public Double y;
    final public Long id;
    
    public PelletPositionMessage(Double x, Double y, Long id){
        this.x = x;
        this.y = y;
        this.id = id;
    }
    
}
