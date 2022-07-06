// GENERATED AUTOMATICALLY FROM 'Assets/Script/Input/AreaSelect.inputactions'

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Utilities;

public class @AreaSelect : IInputActionCollection, IDisposable
{
    public InputActionAsset asset { get; }
    public @AreaSelect()
    {
        asset = InputActionAsset.FromJson(@"{
    ""name"": ""AreaSelect"",
    ""maps"": [
        {
            ""name"": ""controller"",
            ""id"": ""00f9a7a1-b57a-4f6e-a6c2-19e35212f13a"",
            ""actions"": [
                {
                    ""name"": ""Enter key"",
                    ""type"": ""Button"",
                    ""id"": ""61b3adf7-9aba-4f33-8921-650f8ba6cc9e"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """"
                },
                {
                    ""name"": ""Right"",
                    ""type"": ""Button"",
                    ""id"": ""0d22d0c3-5f73-4923-b623-f4f93f5fb27b"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """"
                },
                {
                    ""name"": ""Left"",
                    ""type"": ""Button"",
                    ""id"": ""b3ed365c-504c-4259-bc54-606f8c8e2aa4"",
                    ""expectedControlType"": ""Button"",
                    ""processors"": """",
                    ""interactions"": """"
                }
            ],
            ""bindings"": [
                {
                    ""name"": """",
                    ""id"": ""6a41dfb5-aca0-4159-a7f2-cd3972ee0698"",
                    ""path"": ""<Gamepad>/buttonSouth"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Enter key"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""ede9e4dd-2cfe-4be7-a847-1809be45bc3e"",
                    ""path"": ""<Keyboard>/enter"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Enter key"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""4741da68-a0f0-4306-bf97-d613a4d15318"",
                    ""path"": ""<Gamepad>/rightShoulder"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Right"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""a84b4d83-1459-493d-9916-3af4a290e483"",
                    ""path"": ""<Keyboard>/rightArrow"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Right"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""1c5c9c54-60f8-4116-a53a-ed1b3ec872be"",
                    ""path"": ""<Keyboard>/d"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Right"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""59ea7de0-c2e2-41ce-96e9-c2754c1fa57c"",
                    ""path"": ""<Gamepad>/leftStick/right"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Right"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""33b7b409-12f8-44bb-b0ed-31753abca70b"",
                    ""path"": ""<Keyboard>/leftArrow"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Left"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""6c7c06bd-3ea2-474a-99ea-1a7edbde4e0f"",
                    ""path"": ""<Gamepad>/leftShoulder"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Left"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""403c9abe-8cf0-4b10-aeb1-94344a0b767b"",
                    ""path"": ""<Keyboard>/a"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Left"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                },
                {
                    ""name"": """",
                    ""id"": ""703994bf-3c55-465c-80e3-5852ac1b1e55"",
                    ""path"": ""<Gamepad>/leftStick/left"",
                    ""interactions"": """",
                    ""processors"": """",
                    ""groups"": """",
                    ""action"": ""Left"",
                    ""isComposite"": false,
                    ""isPartOfComposite"": false
                }
            ]
        }
    ],
    ""controlSchemes"": []
}");
        // controller
        m_controller = asset.FindActionMap("controller", throwIfNotFound: true);
        m_controller_Enterkey = m_controller.FindAction("Enter key", throwIfNotFound: true);
        m_controller_Right = m_controller.FindAction("Right", throwIfNotFound: true);
        m_controller_Left = m_controller.FindAction("Left", throwIfNotFound: true);
    }

    public void Dispose()
    {
        UnityEngine.Object.Destroy(asset);
    }

    public InputBinding? bindingMask
    {
        get => asset.bindingMask;
        set => asset.bindingMask = value;
    }

    public ReadOnlyArray<InputDevice>? devices
    {
        get => asset.devices;
        set => asset.devices = value;
    }

    public ReadOnlyArray<InputControlScheme> controlSchemes => asset.controlSchemes;

    public bool Contains(InputAction action)
    {
        return asset.Contains(action);
    }

    public IEnumerator<InputAction> GetEnumerator()
    {
        return asset.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void Enable()
    {
        asset.Enable();
    }

    public void Disable()
    {
        asset.Disable();
    }

    // controller
    private readonly InputActionMap m_controller;
    private IControllerActions m_ControllerActionsCallbackInterface;
    private readonly InputAction m_controller_Enterkey;
    private readonly InputAction m_controller_Right;
    private readonly InputAction m_controller_Left;
    public struct ControllerActions
    {
        private @AreaSelect m_Wrapper;
        public ControllerActions(@AreaSelect wrapper) { m_Wrapper = wrapper; }
        public InputAction @Enterkey => m_Wrapper.m_controller_Enterkey;
        public InputAction @Right => m_Wrapper.m_controller_Right;
        public InputAction @Left => m_Wrapper.m_controller_Left;
        public InputActionMap Get() { return m_Wrapper.m_controller; }
        public void Enable() { Get().Enable(); }
        public void Disable() { Get().Disable(); }
        public bool enabled => Get().enabled;
        public static implicit operator InputActionMap(ControllerActions set) { return set.Get(); }
        public void SetCallbacks(IControllerActions instance)
        {
            if (m_Wrapper.m_ControllerActionsCallbackInterface != null)
            {
                @Enterkey.started -= m_Wrapper.m_ControllerActionsCallbackInterface.OnEnterkey;
                @Enterkey.performed -= m_Wrapper.m_ControllerActionsCallbackInterface.OnEnterkey;
                @Enterkey.canceled -= m_Wrapper.m_ControllerActionsCallbackInterface.OnEnterkey;
                @Right.started -= m_Wrapper.m_ControllerActionsCallbackInterface.OnRight;
                @Right.performed -= m_Wrapper.m_ControllerActionsCallbackInterface.OnRight;
                @Right.canceled -= m_Wrapper.m_ControllerActionsCallbackInterface.OnRight;
                @Left.started -= m_Wrapper.m_ControllerActionsCallbackInterface.OnLeft;
                @Left.performed -= m_Wrapper.m_ControllerActionsCallbackInterface.OnLeft;
                @Left.canceled -= m_Wrapper.m_ControllerActionsCallbackInterface.OnLeft;
            }
            m_Wrapper.m_ControllerActionsCallbackInterface = instance;
            if (instance != null)
            {
                @Enterkey.started += instance.OnEnterkey;
                @Enterkey.performed += instance.OnEnterkey;
                @Enterkey.canceled += instance.OnEnterkey;
                @Right.started += instance.OnRight;
                @Right.performed += instance.OnRight;
                @Right.canceled += instance.OnRight;
                @Left.started += instance.OnLeft;
                @Left.performed += instance.OnLeft;
                @Left.canceled += instance.OnLeft;
            }
        }
    }
    public ControllerActions @controller => new ControllerActions(this);
    public interface IControllerActions
    {
        void OnEnterkey(InputAction.CallbackContext context);
        void OnRight(InputAction.CallbackContext context);
        void OnLeft(InputAction.CallbackContext context);
    }
}
