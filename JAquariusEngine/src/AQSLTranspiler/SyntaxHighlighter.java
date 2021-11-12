package AQSLTranspiler;

import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;
import java.awt.*;

public class SyntaxHighlighter {
    JTextPane textPane;
    StyledDocument styledDocument; //For inserting text with or without colors.
    Style style;
    public SyntaxHighlighter(JTextPane textPane){
        this.textPane = textPane;
        styledDocument = textPane.getStyledDocument();
        style = textPane.addStyle("First style test", null);

        try{
            StyleConstants.setForeground(style, Color.RED);
            styledDocument.insertString(styledDocument.getLength(), "Test0\n", style);
            StyleConstants.setForeground(style, Color.BLUE);
            styledDocument.insertString(styledDocument.getLength(), "Test1\n", style);
        } catch (BadLocationException e) {
            e.printStackTrace();
        }
    }
}
