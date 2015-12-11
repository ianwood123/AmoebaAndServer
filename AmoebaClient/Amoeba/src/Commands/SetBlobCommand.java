/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Commands;

import Game.GameWorld;
import GameObjects.Blob;
import GameObjects.GameObject;
import GameObjects.NameTag;
import Messages.BlobStateMessage;
import java.util.Objects;
import javafx.scene.Node;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 *
 * @author woodi
 */
public class SetBlobCommand implements MessageCommand<BlobStateMessage> {

    GameWorld world;
    BlobStateMessage bsm;

    public SetBlobCommand(BlobStateMessage message, GameWorld gw) {
        world = gw;
        bsm = message;

    }

    @Override
    public void execute() {
        Long id = (long) -1;
        for (GameObject go : world.objects) {
            if (Objects.equals(go.id, bsm.id)) {
                go.updateModel(bsm.x, bsm.y, bsm.size, Color.web(bsm.color));
                go.resetDirt();
                id = go.id;
            } else if (Objects.equals(go.id, bsm.id + 9000)) {
                go.updateModel(bsm.x, bsm.y - (bsm.size/2) - 2, bsm.size, Color.WHITE);
                go.resetDirt();
                break;
            }
        }
        if (id == -1) {
            Blob b = new Blob(bsm.x, bsm.y, bsm.size, Color.web(bsm.color), bsm.id, bsm.username);
            world.addGameObject(b);
        }
    }
}
