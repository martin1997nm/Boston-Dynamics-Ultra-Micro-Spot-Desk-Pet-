package com.fmnumu.szakdolgozat.ui.connection;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import com.fmnumu.szakdolgozat.MainActivity;
import com.fmnumu.szakdolgozat.R;
import com.fmnumu.szakdolgozat.databinding.FragmentConnectionBinding;

public class ConnectionFragment extends Fragment{

    private ConnectionViewModel connectionViewModel;
    private FragmentConnectionBinding binding;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentConnectionBinding.inflate(inflater, container, false);
        View root = binding.getRoot();

        final EditText textBoxMqttAddress = root.findViewById(R.id.textboxMqttBrokerAddr);

        Button connect = root.findViewById(R.id.buttonMqttConnect);
        connect.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view) {
                String mqttAddress = textBoxMqttAddress.getText().toString();
                ((MainActivity)getActivity()).connectMQTT(root, mqttAddress);
            }
        });

        connectionViewModel =
                new ViewModelProvider(this).get(ConnectionViewModel.class);

        return root;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }
}