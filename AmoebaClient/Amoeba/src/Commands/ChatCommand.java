/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Commands;

import Game.GameWorld;
import GameModels.ChatMessageModel;
import GameObjects.ChatMessageObject;
import Messages.ChatMessage;

/**
 *
 * @author woodi
 */
public class ChatCommand implements MessageCommand<ChatMessage>{
    ChatMessage chatmessage;
    GameWorld world;
    
    public ChatCommand(ChatMessage cm, GameWorld gw){
        chatmessage = cm;
        world = gw;
    }
    
    @Override
    public void execute() {
        world.objects.add(new ChatMessageObject(chatmessage.text,new Long(-100),chatmessage.username));
        System.out.println("Got one.");
    }
    
    
}
