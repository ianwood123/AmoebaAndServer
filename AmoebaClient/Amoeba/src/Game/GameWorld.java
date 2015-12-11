/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Game;

import Commands.Command;
import Commands.CommandFactory;
import GameObjects.GameObject;
import GameObjects.Pellet;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;
import javafx.scene.Node;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public class GameWorld implements Runnable {

    public final CommandFactory commandFactory;
    boolean exiting = false;
    protected ConcurrentLinkedQueue<Command> commands;

    public ConcurrentLinkedQueue<GameObject> objects;

    public GameWorld() {
        this.commandFactory = new CommandFactory(this);
        commands = new ConcurrentLinkedQueue();
        objects = new ConcurrentLinkedQueue();
    }

    public void addGameObject(GameObject go) {
        this.objects.add(go);
    }

    public ArrayList<Node> getModels() {
        ArrayList<Node> models = new ArrayList();
        for (GameObject go : this.objects) {
            models.add(go.getModel());
        }
        return models;
    }

    @Override
    public void run() {
        while (!commands.isEmpty()){
            Command c = commands.poll();
            if (c != null){
             c.execute();
            }
        }
        commands.clear();
        for (GameObject go : objects) {
            if (go.tooDirty()) {
                objects.remove(go);
            }
        }
    }
}
