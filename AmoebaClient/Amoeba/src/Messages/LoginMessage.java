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
public class LoginMessage extends Message{
    public final String username;
    public final String password;

    public LoginMessage(String u, String p){
     this.username = u; 
     this.password = p;
     
    }
}