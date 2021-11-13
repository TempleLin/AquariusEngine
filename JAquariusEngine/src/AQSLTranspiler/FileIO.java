package AQSLTranspiler;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;

public class FileIO {
    public String readFileReturnStr(String fileName) {
        try{
            File file = new File(fileName);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String readText = "";
            String strBuffer;
            while ((strBuffer = bufferedReader.readLine()) != null){
                readText = readText + strBuffer + "\n";
            }
            return readText;
        } catch (NullPointerException | FileNotFoundException exception){
            System.out.println(exception.getMessage());
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
        return null;
    }
    public void saveTextAsGLSL(String text, String fileTypeDescription , String fileExtension){
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter fileNameExtensionFilter = new FileNameExtensionFilter(fileTypeDescription, fileExtension);
        fileChooser.addChoosableFileFilter(fileNameExtensionFilter);
        fileChooser.setFileFilter(fileNameExtensionFilter);
        int dialog = fileChooser.showOpenDialog(null);
        if (dialog == JFileChooser.APPROVE_OPTION){
            File file = new File(fileChooser.getSelectedFile().getAbsolutePath());

            try{
                FileWriter fileWriter = new FileWriter(file, false);
                BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
                bufferedWriter.write(text);

                bufferedWriter.flush();
                bufferedWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
