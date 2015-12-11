/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Game;

import Commands.CommandFactory;
import MentalWookieYodels.MessageQueue;
import MentalWookieYodels.NetworkMessageQueue;
import Messages.MessageFactory;

/**
 *
 * @author woodi
 */
public abstract class GameMessageHandler implements Runnable {
    CommandFactory of;
    MessageFactory mf;
    MessageQueue queue;
    NetworkMessageQueue net;
    boolean shuttingDown;
    
    GameMessageHandler(NetworkMessageQueue net, MessageQueue q, CommandFactory of, MessageFactory mf){
        this.net = net;
        this.mf = mf;
        this.queue = q;
        this.of = of;
        this.shuttingDown = false;
    }
    
    public void shutdown(){
        this.shuttingDown = true;
    }

}


