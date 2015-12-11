/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Messages;

import Messages.Message;

/**
 *
 * @author woodi
 */
public class PlainTextMessage extends Message{
    final public String text;
    
    public PlainTextMessage(String txt){
        text = txt;
    }
}

