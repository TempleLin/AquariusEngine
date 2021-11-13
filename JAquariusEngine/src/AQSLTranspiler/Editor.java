package AQSLTranspiler;

// Java Program to create a text editor using java
import com.formdev.flatlaf.FlatDarculaLaf;

import javax.swing.*;
import java.awt.event.*;

class Editor extends JFrame implements ActionListener {
    // Text component
    JTextPane textPane;
    SyntaxHighlighter syntaxHighlighter;
    // Frame
    JFrame frame;

    // Constructor
    public Editor()
    {
        // Create a frame
        frame = new JFrame("AQSLTranspiler");

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        try {
            FlatDarculaLaf.setup();
            // Set metal look and feel
            UIManager.setLookAndFeel("com.formdev.flatlaf.FlatDarculaLaf");

            // Set theme to ocean
            //MetalLookAndFeel.setCurrentTheme(new OceanTheme());
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // Text component
        textPane = new JTextPane();

        JMenuBar menuBar = new JMenuBar();
        JMenu menu0 = new JMenu("AQShaderType");
        JMenu menu1 = new JMenu("ExportShader");

        JMenu menu0Item0 = new JMenu("SimpleBox2D");

        JMenuItem menu0Item0_0 = new JMenuItem("VertexShader");
        JMenuItem menu0Item0_1 = new JMenuItem("FragmentShader");
        menu0Item0_0.setActionCommand("SimpleBox2D_VS");
        menu0Item0_1.setActionCommand("SimpleBox2D_FS");

        menu0Item0_0.addActionListener(this);
        menu0Item0_1.addActionListener(this);

        menu0Item0.add(menu0Item0_0);
        menu0Item0.add(menu0Item0_1);
        menu0.add(menu0Item0);


        JMenuItem menu1Item0 = new JMenuItem("ToCPPHeader");
        JMenuItem menu1Item1 = new JMenuItem("ToJavaFile");
        JMenuItem menu1Item2 = new JMenuItem("ToShaderFile");

        menu1Item0.addActionListener(this);
        menu1Item1.addActionListener(this);
        menu1Item2.addActionListener(this);

        menu1.add(menu1Item0);
        menu1.add(menu1Item1);
        menu1.add(menu1Item2);

        menuBar.add(menu0);
        menuBar.add(menu1);

        textPane.setEditorKit(new TabSizeEditorKit());
        syntaxHighlighter = new SyntaxHighlighter(textPane);

        frame.setJMenuBar(menuBar);
        frame.add(textPane);
        frame.setSize(800, 800);
        frame.setVisible(true);


//        // Create a menubar
//        JMenuBar mb = new JMenuBar();
//
//        // Create amenu for menu
//        JMenu m1 = new JMenu("File");
//
//        // Create menu items
//        JMenuItem mi1 = new JMenuItem("New");
//        JMenuItem mi2 = new JMenuItem("Open");
//        JMenuItem mi3 = new JMenuItem("Save");
//        JMenuItem mi9 = new JMenuItem("Print");
//
//        // Add action listener
//        mi1.addActionListener(this);
//        mi2.addActionListener(this);
//        mi3.addActionListener(this);
//        mi9.addActionListener(this);
//
//        m1.add(mi1);
//        m1.add(mi2);
//        m1.add(mi3);
//        m1.add(mi9);
//
//        // Create amenu for menu
//        JMenu m2 = new JMenu("Edit");
//
//        // Create menu items
//        JMenuItem mi4 = new JMenuItem("cut");
//        JMenuItem mi5 = new JMenuItem("copy");
//        JMenuItem mi6 = new JMenuItem("paste");
//
//        // Add action listener
//        mi4.addActionListener(this);
//        mi5.addActionListener(this);
//        mi6.addActionListener(this);
//
//        m2.add(mi4);
//        m2.add(mi5);
//        m2.add(mi6);
//
//        JMenu mShaderType = new JMenu("ShaderType");
//        mShaderType.add(new JMenuItem("SimpleBox2D"));
//
//        mb.add(m1);
//        mb.add(m2);
//        mb.add(mShaderType);
//
//        f.setJMenuBar(mb);
//        f.add(t);
//        f.setSize(500, 500);
//        f.show();
    }

    // If a button is pressed
    public void actionPerformed(ActionEvent e)
    {
        FileIO fileIO = new FileIO();
        switch (e.getActionCommand()){
            case "SimpleBox2D_VS":
                textPane.setText(fileIO.readFileReturnStr("two_d_tex_vs.glsl"));
                System.out.println("SimpleBox2D_VS");
                break;
            case "SimpleBox2D_FS":
                textPane.setText(fileIO.readFileReturnStr("two_d_tex_fs.glsl"));
                System.out.println("SimpleBox2D_FS");
                break;
            case "ToShaderFile":
                fileIO.saveTextAsFile(textPane.getText(), new String[]{"glsl"}, new String[]{"glsl"}, FileIO.FileTypes.GLSL);
                break;
            case "ToJavaFile":
                fileIO.saveTextAsFile(textPane.getText(), new String[]{"java"}, new String[]{"java"}, FileIO.FileTypes.JAVAFILE);
                break;
            case "ToCPPHeader":
                fileIO.saveTextAsFile(textPane.getText(), new String[]{"hpp", "h"}, new String[]{"hpp", "h"}, FileIO.FileTypes.CPPHEADER);
                break;
        }

//        String s = e.getActionCommand();
//        if (s.equals("SimpleBox2D")){
//            System.out.println("SimpleBox2D");
//        } else if (s.equals("SimpleBox2D_VS")){
//            System.out.println("SimpleBox2D_VS");
//        }
//        if (s.equals("cut")) {
//            textPane.cut();
//        }
//        else if (s.equals("copy")) {
//            textPane.copy();
//        }
//        else if (s.equals("paste")) {
//            textPane.paste();
//        }
//        else if (s.equals("Save")) {
//            // Create an object of JFileChooser class
//            JFileChooser j = new JFileChooser("f:");
//
//            // Invoke the showsSaveDialog function to show the save dialog
//            int r = j.showSaveDialog(null);
//
//            if (r == JFileChooser.APPROVE_OPTION) {
//
//                // Set the label to the path of the selected directory
//                File fi = new File(j.getSelectedFile().getAbsolutePath());
//
//                try {
//                    // Create a file writer
//                    FileWriter wr = new FileWriter(fi, false);
//
//                    // Create buffered writer to write
//                    BufferedWriter w = new BufferedWriter(wr);
//
//                    // Write
//                    w.write(textPane.getText());
//
//                    w.flush();
//                    w.close();
//                }
//                catch (Exception evt) {
//                    JOptionPane.showMessageDialog(frame, evt.getMessage());
//                }
//            }
//            // If the user cancelled the operation
//            else
//                JOptionPane.showMessageDialog(frame, "the user cancelled the operation");
//        }
//        else if (s.equals("Print")) {
//            try {
//                // print the file
//                textPane.print();
//            }
//            catch (Exception evt) {
//                JOptionPane.showMessageDialog(frame, evt.getMessage());
//            }
//        }
//        else if (s.equals("Open")) {
//            // Create an object of JFileChooser class
//            JFileChooser j = new JFileChooser("f:");
//
//            // Invoke the showsOpenDialog function to show the save dialog
//            int r = j.showOpenDialog(null);
//
//            // If the user selects a file
//            if (r == JFileChooser.APPROVE_OPTION) {
//                // Set the label to the path of the selected directory
//                File fi = new File(j.getSelectedFile().getAbsolutePath());
//
//                try {
//                    // String
//                    String s1 = "", sl = "";
//
//                    // File reader
//                    FileReader fr = new FileReader(fi);
//
//                    // Buffered reader
//                    BufferedReader br = new BufferedReader(fr);
//
//                    // Initialize sl
//                    sl = br.readLine();
//
//                    // Take the input from the file
//                    while ((s1 = br.readLine()) != null) {
//                        sl = sl + "\n" + s1;
//                    }
//
//                    // Set the text
//                    textPane.setText(sl);
//                }
//                catch (Exception evt) {
//                    JOptionPane.showMessageDialog(frame, evt.getMessage());
//                }
//            }
//            // If the user cancelled the operation
//            else
//                JOptionPane.showMessageDialog(frame, "the user cancelled the operation");
//        }
//        else if (s.equals("New")) {
//            textPane.setText("");
//        }
    }

    }
