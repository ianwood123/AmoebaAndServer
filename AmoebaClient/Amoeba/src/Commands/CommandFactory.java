/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Commands;

import Game.GameWorld;
import Messages.Message;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author woodi
 */
public class CommandFactory{
    public static GameWorld world;
    public CommandFactory(){
        register(ChatCommand.class);
        register(SetPelletCommand.class);
        register(SetBlobCommand.class); 
    }
    public CommandFactory(GameWorld world){
        this();
        this.world = world;
    }
    static ArrayList<Class> commandClasses = new ArrayList();
    
    public final void register(Class c){
        commandClasses.add(c);
    }
    
    public static Command getCommandObject(Message m){
       
            Class clazz = m.getClass();
            
            for(Class c : commandClasses){
                if(getParameterClass(c).equals(clazz)){
                    try {
                        return (Command) c.getConstructor(clazz,world.getClass()).newInstance(m,world);
                    } catch (NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
                        Logger.getLogger(CommandFactory.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }

        return null;
        
    }

    public static Type getInterfaceGenericType(Class c){
        Type[] genericInterfaces = c.getGenericInterfaces();
        Type[] genericTypes = null;
        Class<?> clazz;
                for (Type genericInterface : genericInterfaces) {
                    if (genericInterface instanceof ParameterizedType) {
                        genericTypes = ((ParameterizedType) genericInterface).getActualTypeArguments();
                               
                    } 
                }
                
        return genericTypes[0];
    }
    
  public static Class<?> getParameterClass(Class c) {
    return (Class<?>) (((ParameterizedType)c.getGenericInterfaces()[0]).getActualTypeArguments()[0]);
  }

}


