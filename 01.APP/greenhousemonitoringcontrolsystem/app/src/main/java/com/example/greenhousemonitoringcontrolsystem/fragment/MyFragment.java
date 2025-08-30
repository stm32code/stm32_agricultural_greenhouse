package com.example.greenhousemonitoringcontrolsystem.fragment;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.example.greenhousemonitoringcontrolsystem.MainActivity;
import com.example.greenhousemonitoringcontrolsystem.R;
import com.example.greenhousemonitoringcontrolsystem.socket.SocketClientThread;
import com.example.greenhousemonitoringcontrolsystem.utils.Common;

public class MyFragment extends Fragment {

    private EditText ipText, portText;
    private TextView connectBtn;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_my, container, false);

        initView(view);
        return view;
    }

    private void initView(View view) {
        ipText = view.findViewById(R.id.ipText);
        portText = view.findViewById(R.id.portText);
        connectBtn = view.findViewById(R.id.connectBtn);

        connectBtn.setOnClickListener(view1 -> {
            if (Common.sClientThread != null) {
                Common.sClientThread.cancel();
            }
            Common.sClientThread = null;
            String ip = ipText.getText().toString();
            String port = portText.getText().toString();
            Common.SOCKET_IP = ip;
            Common.SOCKET_PORT = port;
            Common.sClientThread = new SocketClientThread(ip, Integer.parseInt(port), MainActivity.myHandler);
            Common.sClientThread.start();
        });
    }
}