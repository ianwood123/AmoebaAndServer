/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Game;

import Commands.CommandFactory;
import Exceptions.MessageException;
import Exceptions.NonExistentFieldException;
import MentalWookieYodels.MessageQueue;
import MentalWookieYodels.NetworkMessageQueue;
import Messages.MessageFactory;
import Messages.NetworkMessage;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author woodi
 */
public class GameOutputHandler extends GameMessageHandler {

    public GameOutputHandler(NetworkMessageQueue net, MessageQueue q, CommandFactory of, MessageFactory mf) {
        super(net, q, of, mf);
    }

    @Override
    public void run() {
        if (!queue.isEmpty()) {
            NetworkMessage m = null;
            try {
                m = mf.createNetworkMessage(queue.getNextMessage());
            } catch (MessageException | NonExistentFieldException ex) {
                Logger.getLogger(GameOutputHandler.class.getName()).log(Level.SEVERE, null, ex);
            }
            if (m != null) {
                System.out.println(m);
                this.net.add(m);
            }

        }
    }

}
