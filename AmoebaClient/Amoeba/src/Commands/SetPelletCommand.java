/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Commands;

import Game.GameWorld;
import GameObjects.GameObject;
import GameObjects.Pellet;
import Messages.PelletPositionMessage;
import java.util.Objects;
import java.util.Random;
import javafx.scene.paint.Color;

/**
 *
 * @author woodi
 */
public class SetPelletCommand implements MessageCommand<PelletPositionMessage> {

    Random r = new Random();

    GameWorld world;
    PelletPositionMessage ppm;

    public SetPelletCommand(PelletPositionMessage message, GameWorld world) {
        this.world = world;
        ppm = message;
    }

    @Override
    public void execute() {
        Long id = new Long(-1);
        for (GameObject go : world.objects) {
            if (Objects.equals(go.id, ppm.id)) {
                go.updateModel(ppm.x, ppm.y, new Double(0), new Color(r.nextFloat(), r.nextFloat(), r.nextFloat(), 1));
                go.resetDirt();
                id = go.id;
            }
        }
        if (id == -1) {
            this.world.addGameObject(new Pellet(ppm.x, ppm.y, new Color(r.nextFloat(), r.nextFloat(), r.nextFloat(), 1), ppm.id));
        }
    }
}
