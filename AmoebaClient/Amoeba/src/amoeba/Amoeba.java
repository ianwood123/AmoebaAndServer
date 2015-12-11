/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package amoeba;

import Exceptions.MessageException;
import Exceptions.NonExistentFieldException;
import Game.GameController;
import MentalWookieYodels.Codec;
import MentalWookieYodels.CustomCodec;
import MentalWookieYodels.MessageQueue;
import MentalWookieYodels.NetworkController;
import MentalWookieYodels.NetworkMessageQueue;
import Messages.ChatMessage;
import Messages.DefaultMessageFactory;
import Messages.LoginMessage;
import Messages.LogoutMessage;
import Messages.MoveTowardCoordinatesMessage;
import Messages.MessageFactory;
import Messages.NetworkMessage;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Background;
import javafx.scene.layout.*;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.paint.*;
import javafx.scene.shape.*;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.util.Duration;

/**
 *
 * @author woodi
 */
public class Amoeba extends Application {

    NetworkController nc;
    NetworkMessageQueue outgoing;
    NetworkMessageQueue incoming;
    MessageQueue in;
    MessageQueue out;
    MessageFactory mf;
    GameController gc;
    Codec codec = new CustomCodec();
    Timeline timeline = new Timeline();
    double x, y;
    boolean send;
    TextField chatbox = new TextField();
    boolean typing = false;

    @Override
    public void start(Stage primaryStage) {
        mf = new DefaultMessageFactory();
        in = new MessageQueue();
        out = new MessageQueue();
        outgoing = new NetworkMessageQueue();
        incoming = new NetworkMessageQueue();
        chatbox.setEditable(true);
        chatbox.setTranslateY(500);
        
//        chatbox.setTranslateY(500);
//        chatbox.setTranslateX(50);
        nc = new NetworkController("localhost", 8080, codec, incoming, outgoing);

        gc = new GameController(incoming, outgoing, mf, in, out);
        AnchorPane container = new AnchorPane();
        AnchorPane.setLeftAnchor(chatbox, 0.0);
        AnchorPane.setBottomAnchor(chatbox, 0.0);
        container.setOnKeyPressed((e)->{
            if(e.getCode().equals(KeyCode.ENTER)){
                if(typing){
                    typing = false;
                    if(chatbox.getText().isEmpty()){
                    return;
                    }
                    try {
                        outgoing.add(mf.createNetworkMessage(new ChatMessage("",chatbox.getText())));
                    } catch (MessageException | NonExistentFieldException ex) {
                    }
                }
                else{
                    chatbox.requestFocus();
                    typing = true;
                }
            }
        });
        Group renderPane = new Group();

        container.getChildren().add(renderPane);
        container.getChildren().add(chatbox);
        container.setMinSize(800, 600);
        send = false;
        Button btn = new Button();

        TextField username = new TextField();
        username.setEditable(true);
        username.setPromptText("Username");
        username.setMaxSize(200, 50);
        username.setAlignment(Pos.CENTER);

        MediaPlayer music = new MediaPlayer(new Media("http://23.28.17.54/network/Timothy/Music/new/WhenCanISeeYouAgain(WelcomeToTheRythmOfTheNight)-OwlCity.mp3"));
        music.setCycleCount(MediaPlayer.INDEFINITE);
        
        btn.setText("Play");
        btn.setOnAction((ActionEvent event) -> {
            try {
                outgoing.add(mf.createNetworkMessage(new LoginMessage(username.getText(), "")));
                nc.connect();
                music.play();

                //if successful, switch to game view
            } catch (MessageException | NonExistentFieldException ex) {
                Logger.getLogger(Amoeba.class.getName()).log(Level.SEVERE, null, ex);
                Alert a = new Alert(Alert.AlertType.ERROR);
                a.setTitle("Error 3401");
                a.setHeaderText("Error 3401: Programmers stuck in limbo.");
                a.setContentText("We have dispatched a team of monkeys to fix this error. In the meantime, please try again.");
                a.show();
            } finally {
                if (nc.checkConnection()) {
                    System.out.println("Successfully connected to server. ");
                    primaryStage.setScene(new Scene(container));
                } else {
                    System.exit(1);
                }
            }
        });
        VBox vb = new VBox(username, btn);

        vb.setAlignment(Pos.CENTER);
        StackPane root = new StackPane(vb);

        Scene scene = new Scene(root, 800, 600);

        primaryStage.setOnCloseRequest((WindowEvent event) -> {
            LogoutMessage m = new LogoutMessage();
            try {
                outgoing.add(mf.createNetworkMessage(m));
                Thread.sleep(100);
            } catch (MessageException | NonExistentFieldException | InterruptedException ex) {
                Logger.getLogger(Amoeba.class.getName()).log(Level.SEVERE, null, ex);
            }
            System.exit(0);
        });

        BackgroundImage bg = new BackgroundImage(new Image("http://23.28.17.54/network/Timothy/wallpapers/114043-Bluelectriksmog.jpg"),
        BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.CENTER,
          BackgroundSize.DEFAULT);
        
        container.setBackground(new Background(bg));
        
        container.setOnMouseReleased((e) -> {
            this.send = false;
        });

        container.setOnMouseDragged((e) -> {
            this.send = true;
            this.x = e.getX();
            this.y = e.getY();
        });

        timeline.getKeyFrames().add(new KeyFrame(Duration.seconds(0.016), (e) -> {
            render(renderPane);
            
            if (this.send) {
                try {
                    outgoing.add(mf.createNetworkMessage(new MoveTowardCoordinatesMessage(this.x, this.y)));
                } catch (MessageException | NonExistentFieldException ex) {
                    Logger.getLogger(Amoeba.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        primaryStage.setTitle("Amoeba");
        primaryStage.setScene(scene);
        primaryStage.show();

        timeline.play();

    }

    private void render(Group p) {
        Rectangle border = new Rectangle(0, 0, 800, 600);
        border.setFill(Color.TRANSPARENT);
        border.setStroke(Color.BLACK);
        p.getChildren().clear();
        p.getChildren().add(border);
        p.getChildren().addAll(gc.getWorld().getModels());
        p.getChildren().add(chatbox);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
